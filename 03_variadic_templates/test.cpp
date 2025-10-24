/* 
A random example of something not needing to name the type, and using the variadic templates
*/

#include <iostream>
#include <type_traits>
#include <tuple>

template <int ...lst>
struct myType {};


// PRINTN //////////////////////////////////////////////
template <typename LAST>
void printn(LAST t) {
    std::cout << t << std::endl;
}

template <typename T0, typename ...T1toN>
void printn(T0 t, T1toN... rest) {
    std::cout << t << ", ";
    printn(rest...);
}

// MY STUFF //////////////////////////////////////////////
int addOne(int x) {
    return x + 1;
}

template <int ...lst>
void func(myType<lst...>) { // note how we don't care about the actual variable at all
    printn(addOne(lst)...); // printn(addOne(lst0), addOne(lst1), ...); I kinda get it...
}

// this is another example where we don't care about the actual variable
void func(int) {
    std::cout << "this is unrelated" << std::endl;
}

int main() {
    struct myType<3, 4, 5> x{};
    func(x); // 4, 5, 6
    func(3); // this is unrelated
}