#include <iostream>
#include <type_traits>
// g++ -std=c++20 02.cpp


template <typename T>
struct strip_pointer {
    using type = T; // using: essentially a typedef, it's not actually stored in the struct
    // if you refer to it, it's just a compile-time type.
};

// use :: when dealing with static members, typedefs. Use . when dealing with stuff that's in the struct at runtime

// NOTE: struct definitions are type definitions btw, so these are types.
// This is typical metaprogramming, both the input and output are types
template <typename T>
struct strip_pointer<T*> {
    using type = T;
};

template <typename T>
using strip_pointer_t = typename strip_pointer<T>::type;

template <typename T>
void print1(T x) {
    using T_without_pointer = strip_pointer_t<T>;
    if constexpr (std::is_floating_point<T_without_pointer>::value) {
        std::cout << "found a floating point" << std::endl;
    } else {
        std::cout << "no floating point found" << std::endl;
    }
}

int main() {
    float x = 0.5f;
    print1(x);
    print1(&x);
    print1('a');
}