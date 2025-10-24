#pragma once
#include <iostream>

// This defines your class
class Player {
public:
    int hp;
    int shield;

    Player(int _hp=100, int _shield=0);
    ~Player();

    void add_shield(int amount);
};