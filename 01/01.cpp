#include <iostream>
#include <type_traits>
// g++ -std=c++20 01.cpp

template<typename T>
struct is_pointer{
    static constexpr bool value = false;
};

// This is a partial specialization
// It will try to peel off a * from the pointer basically
template<typename T>
struct is_pointer<T*> {
    static constexpr bool value = true;
};

// After C++17(chatGPT), you can produce templated variables
// constexpr means value is known at compile time
// Inline: the compiler will elide multiple definitions of the function[https://stackoverflow.com/questions/156438/what-does-it-mean-for-a-c-function-to-be-inline]
template<class T>
inline constexpr bool is_pointer_v = is_pointer<T>::value;

template<typename T>
void print1(T t) {
    // When compiling, this GOTO will not be in the assembly
    if constexpr (is_pointer_v<T>) {
        std::cout << *t << std::endl;
    } else {
        std::cout << t << std::endl;
    }
}

int main() {
    print1(1); // T is deduced from the argument. This is the same as print1<int>(1);
    int x = 2;
    print1<int *>(&x);
}