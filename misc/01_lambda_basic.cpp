// https://learn.microsoft.com/en-us/cpp/cpp/lambda-expressions-in-cpp?view=msvc-170
#include <iostream>

// Capture clause
// [] means don't access surrounding vars
// [&] means capture all surrounding vars by reference
// [=] means capture all surrounding vars by value
// you can do [x, &y], [&, x], [=, &y]
// you can pass in references  in like [&, *this] (this still captures by value)

int main() {
    int i = 1;
    auto f = [](int i) {return i + 1;};
    int j = f(i);
    std::cout << j << std::endl;

    auto g = [&]() {i++;};
    g();
    std::cout << i << std::endl;

    auto h = [=]() mutable {
        // without mutable, i gets passed as an unmodifiable lvalue
        // with mutable, we can modify i in the internal scope
        i++;
        return i + 1;
    };
    int k = h();
    std::cout << i << std::endl; 
    std::cout << k << std::endl; // 4
}
// TLDR (fortnite): [=] is like making a copy of loot — you can’t alter the original; mutable lets you mess with your copy, [&] lets you touch the real loot.