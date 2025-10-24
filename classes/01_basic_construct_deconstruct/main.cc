#include <iostream>
#include "player.h" // include the header cuz...yknow

// when you compile stuff, don't add the h files, those get included by the .cc files
// g++ main.cc player.cc

int main() {
    // Instantiating a class basically makes a struct
    Player p(100, 50);
    p.add_shield(30);
    std::cout << p.shield << std::endl;

    // instantiate on the heap
    Player* p2 = new Player(100, 50);
    delete p2;

    // p's deconstructor should be called here since main is ending
}