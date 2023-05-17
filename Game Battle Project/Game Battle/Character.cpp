//
//  Character.cpp
//  Game Battle
//
//  Created by Dylan Hilton on 4/24/21.
//

#include "Character.h"

using namespace std;

void Character::setHealth(int characterHealth) {
    health = characterHealth;
}

void Character::setName(string characterName) {
    name = characterName;
}

void Character::setLevel(int characterLevel) {
    level = characterLevel;
    srand(static_cast<unsigned int>(time(0))); //since all additional classes inherit from this class, I set the seed of my random function here using time(0)
}

void Character::setRace(string characterRace) {
    race = characterRace;
}

int Character::getHealth() {
    return health;
}

string Character::getName() {
    return name;
}

int Character::getLevel() {
    return level;
}

string Character::getRace() {
    return race;
}
