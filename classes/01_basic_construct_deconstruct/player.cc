#include "player.h"

// Here, we can implement all of our functions

// : is initializer list, so it instantly initializes hp to _hp, shield to _shield. Initializes stuff directly instead of default construct and then assigning
// This implements the Player(constructor) in the player class
Player::Player(int _hp, int _shield) : hp(_hp), shield(_shield) {
    std::cout << "Player spawned" << std::endl; // we can use std since our .h has iostream
}

// This is the destructor
Player::~Player() {
    std::cout << "Player destroyed" << std::endl;
}

void Player::add_shield(int amount) {
    this->shield += amount; // you get a this, which is a Player *. You could just write shield here, this would be implied
}