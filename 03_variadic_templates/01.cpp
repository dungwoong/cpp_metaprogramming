#include <iostream>
#include <type_traits>
#include <tuple>

/*
We want printn(9, "hello", 1.5, true);
We can't use for loops in our templates!

Then, what if we want to print a tuple as well?
*/

// We NEED this to go before the other printn, because when we recursively call it,
// only stuff before that definition is considered.
// So if we put it after, it won't find this base-case.
template <typename LAST>
void printn(LAST t) {
    std::cout << t << std::endl;
}

// ... is a pack, like in python
// before means compact it, after means expand it
template <typename T0, typename ...T1toN>
void printn(T0 t, T1toN... rest) { // this becomes e.g. int rest0, double rest1, etc.
    std::cout << t << ", ";
    printn(rest...); // so ... expands the parameters back here
}

// we need indices in the template here so we can expand them
// also otherwise what else will be put in std::index_sequence<> yknow
template<typename TUPLE, std::size_t ... indices>
void print_tuple_impl(TUPLE t, std::index_sequence<indices...>) { // the second arg has no name, because we only care about the indices. We could literally call it x if we wanted
    printn(std::get<indices>(t)...); // this is a pack expansion so it expands OVER indices, printn(get<0>(t), get<1>(t)...)    
}

template<typename TUPLE>
void print_tuple(TUPLE t) {
    // the {} at the end makes a temporary object of that type(aka initializing the range)
    // otherwise it's like writing range in python with no ()
    print_tuple_impl(t, std::make_index_sequence<std::tuple_size<TUPLE>::value>{});
}

int main() {
    std::cout << std::boolalpha;
    printn(9, "hello", 1.5, true);

    auto tuple = std::make_tuple(9, "hello", 1.5, true);
    print_tuple(tuple);
}

// he also shows an example with std::forward, how you can forward stuff while unrolling the thing but that's okay...