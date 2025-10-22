/*
A tuple is a variadic template in the standard library. e.g.

>> std::tuple<int, bool> t;
>> std::tuple<int, bool, float, string> t2;

We will write a contains_type<double, std::tuple<...>> metafunction
>> std::tuple<int, bool, float> t;
>> contains_type<double, decltype(t)>::value == false
*/

// NOTE: decltype takes in an expression and gives you back the type, you use it when it's too hard to write the actual type out

#include <iostream>
#include <vector>
#include <string>
#include <tuple>

// The first tip is to try a mock function on a list of strings like this, without using for loops, etc.
// We want to use recursion, that we will handle with template specialization later
// const stops us from copying the string into the function for pass by value
bool contains(const std::string &search, const std::vector<std::string> &v, size_t start_from=0) {
    if (v[start_from] == search) {
        return true;
    } else {
        if (start_from == v.size() - 1) {
            return false;
        } else {
            return contains(search, v, start_from + 1);
        }
    }
}


// We can make an IF type, where the output type will be then/else, based on the condition
// condition must be constexpr though, we can run static asserts on it for example.
template <bool condition, typename THEN, typename ELSE>
struct if_;

template <typename THEN, typename ELSE>
struct if_<true, THEN, ELSE> {
    using type = THEN;
};

template <typename THEN, typename ELSE>
struct if_<false, THEN, ELSE> {
    using type = ELSE;
};


// We will use std::false_type and std::true type. Think of it as type::value is a bool
// Each specialization needs a value or else the compiler will crash out
// we want to inherit from std::true_type / std::false_type to get the value trait
template <typename SEARCH, typename TUPLE, size_t start_from=0>
struct contains_type :
    if_< // IF
        std::is_same<std::tuple_element_t<start_from, TUPLE>, SEARCH>::value,
        // THEN
        std::true_type,
        // ELSE
        typename if_ < // IF. For some compilers, you may need typename here. It let's the compiler know something is a type
            (start_from == std::tuple_size<TUPLE>::value - 1),
            //THEN
            std::false_type,
            // ELSE
            contains_type<SEARCH, TUPLE, start_from + 1>
        >::type
    >::type
{};
// So we inherit from whatever that if gives us, which could be a true type or a false type

/*
TYPENAME QUICK LESSON

template <typename T>
void foo() {
    T::x * b; // is this declaring a pointer or doing multiplication?
}

struct A { using x = int; } // passing this in would cause foo to declare a pointer
struct A { static int x = 10; } // passing this in would cause us to do multiplication

but if you do typename T::x * b;, the compiler knows T::x is supposed to be a type
but if you did something like T b; we KNOW that T must be a type, typename is not required.


You can also use template keyword to make sure you're using a template and not < and > for comparisons
T::template function<int()>f;

but in cases where the compiler KNOWS it's expecting a type/template, the typename/template keywords may be ILLEGAL! e.g. with the first if_ above
*/

int main() {
    std::vector<std::string> vec {"int", "bool", "float"};

    // boolalpha is just a formatting flag to print true/false instead of 1/0
    std::cout << std::boolalpha << contains("bool", vec) << std::endl; // t
    std::cout << std::boolalpha << contains("double", vec) << std::endl; // f

    std::tuple<int, bool, float> tuple;
    std::cout << std::boolalpha << contains_type<bool, decltype(tuple)>::value << std::endl; // t
}