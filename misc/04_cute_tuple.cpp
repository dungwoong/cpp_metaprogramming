// cute/container/tuple.hpp
// they have a require macro that helps with their printing. Let's test it out here.

#include <iostream>
#include <type_traits>

#define _REQUIRE(...) typename enable_if<(__VA_ARGS__)>::type* = nullptr

struct A {
    int x;
};

struct B {
    int y;
};

// enable_if
// enable_if will give us void if condition is true
// if false, it has no type parameter, it gives us substitution failure
template <bool COND, typename T=void>
struct enable_if {};

template <typename T>
struct enable_if<true, T> {
    using type = T;
};

// Easy is_A struct
template <typename T>
struct is_A : std::false_type {};

template <>
struct is_A<A> : std::true_type {};

// so this expands into enable_if<(__VA_ARGS__)>::type* = nullptr
// either the ::type part just fails, or we get void* = nullptr, which is valid
template <typename T, _REQUIRE(is_A<T>::value)>
void print(T x) {
    std::cout << x.x << std::endl;
}

int main() {
    A a{1};
    B b{2};
    print(a);
}