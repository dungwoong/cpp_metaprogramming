#include <iostream>

struct Test {
    int x;
    static int y; // exists once, takes up space outside the struct.
    constexpr static int z = 99; // compile-time constant, no storage per object
    void foo() {x++;}
    int bar();
};

// You can declare stuff outside of the struct
int Test::y = 0;
int Test::bar() {return this->x;};

int main() {
    Test x{1}; // or struct Test x;
    x.y = 4;
    std::cout << Test::z << std::endl;
    std::cout << Test::y << std::endl;
    x.foo();
    std::cout << x.bar() << std::endl;
}