#include <iostream>
#include <list>
#include <vector>
#include <string>
#include <tuple>
#include <type_traits>

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


// wait so this would not copy search, but disallow modifications
bool contains(const std::string& search, std::list<std::string> l) {
    if (l.empty()) {
        return false;
    } else {
        if (search == l.front()) {
            return true;
        } else {
            l.pop_front(); // since pass by value so we're fine
            return contains(search, l);
        }
    }

}

template <typename ...> // ignore the values, normally it would be typname ...x for example
struct type_list{};

// 1. The empty function
template <typename LIST>
struct empty : std::false_type{};

template <> // empty only if nothing in the template
struct empty<type_list<>> : std::true_type{};

static_assert(empty<type_list<>>::value); // we can do compile-time assertions!

// 2. The front function
template <typename LIST>
struct front; // we're just declaring, not defining the struct so no need for {}. This struct will not be defined for empty type lists.

template <typename T0, typename ...T1toN>
struct front<type_list<T0, T1toN...>> {
    using type = T0;
};

static_assert(std::is_same_v<front<type_list<int, bool>>::type, int>);

// 3. Pop front
template<typename LIST>
struct pop_front;

template<typename T0, typename ... T1toN>
struct pop_front<type_list<T0, T1toN...>> {
    using type = type_list<T1toN...>;
};

static_assert(std::is_same_v<pop_front<type_list<bool, float>>::type, type_list<float>>);


// 4. Aliases
template <typename LIST>
using front_t = typename front<LIST>::type;

template <typename LIST>
using pop_front_t = typename pop_front<LIST>::type;

// I swear static is not needed here, we need inline or something...
template <typename LIST>
static constexpr bool empty_v = empty<LIST>::value;


template <typename SEARCH, typename LIST>
struct contains_type; // add forward declaration before non_empty_contains_type

template <typename SEARCH, typename LIST>
struct non_empty_contains_type:
    if_ <
        std::is_same_v<SEARCH, front_t<LIST>>,
        std::true_type,
        contains_type<SEARCH, pop_front_t<LIST>>
    >::type
{};

template <typename SEARCH, typename LIST>
struct contains_type : 
    if_ <
        empty_v<LIST>,
        std::false_type,
        non_empty_contains_type<SEARCH, LIST>
    >::type{}; // need to call ::type to get the true_type or false_type

// BUG: when you call the first if_ on an empty list, it should just return false_type, but that's not how templates work
// it has to fill out everything, including that if_ yknow like you can't do if <false, ...> like the second arg will be evaluated
// The compiler can't even put a type in there, it's just like if <false, if <error type>> kinda
// - Option 1: create a struct none{} and just set it to that type when the list is empty
// - Option 2: create the new non_empty_contains_type. Just notice that the template params are just the list and whatever, so when the compiler
// tries to do substitutions, it won't have any problems. 


int main() {
    std::list<std::string> list{"int", "bool", "double"};
    std::cout << std::boolalpha;
    std::cout << contains("bool", list) << std::endl; // t


    type_list<int, bool, double> types;
    type_list<> types2;
    std::cout << contains_type<float, decltype(types)>::value << std::endl; // f
    std::cout << contains_type<double, decltype(types)>::value << std::endl; // t
    std::cout << contains_type<double, decltype(types2)>::value << std::endl; // f
}