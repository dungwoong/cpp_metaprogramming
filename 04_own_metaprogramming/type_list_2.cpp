#include <iostream>
#include <list>
#include <vector>
#include <string>
#include <tuple>
#include <type_traits>

// g++ -std=c++20 type_list_2.cpp

template <typename ...>
struct type_list{};

template <typename SEARCH, typename LIST>
struct contains {
    static constexpr bool value = false;
};

template <typename SEARCH, typename T0, typename ...T1toN>
struct contains<SEARCH, type_list<T0, T1toN...>> {
    static constexpr bool value = std::is_same_v<T0, SEARCH> || contains<SEARCH, type_list<T1toN...>>::value;
};

template <typename SEARCH, typename LIST>
inline constexpr bool contains_v = contains<SEARCH, LIST>::value;

int main() {
    type_list<double, float> tl;
    std::cout << std::boolalpha;
    std::cout << contains_v<float, decltype(tl)> << std::endl;
    std::cout << contains_v<int, decltype(tl)> << std::endl;
}