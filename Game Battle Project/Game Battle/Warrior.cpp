//
//  Warrior.cpp
//  Game Battle
//
//  Created by Dylan Hilton on 4/24/21.
//

#include "Warrior.h"

Warrior::Warrior() {
    setName("Unknown");
    setRace("Unknown");
    setLevel(0);
    setHealth(100);
    stamina = 3;
    weapon = "None";
}

Warrior::Warrior(string _name, string _race, int _level, int _health, int _stamina, string _weapon) {
    setName(_name);
    setRace(_race);
    setLevel(_level);
    setHealth(_health);
    stamina = _stamina;
    weapon = _weapon;
}

void Warrior::setStamina(int characterStamina) {
    stamina = characterStamina;
}

void Warrior::setWeapon(string characterWeapon) {
    weapon = characterWeapon;
}

int Warrior::getStamina() {
    return stamina;
}

string Warrior::getWeapon() {
    return weapon;
}

void Warrior::printInfo() {
    cout << "Warrior information:" << endl; //all the printInfo() functions follow this basic format, just some variables change depending on the character type (i.e since this is a warrior, it prints "warrior information," and the variables weapon and stamina are unique to warriors only)
    cout << "   Name: " << getName() << endl;
    cout << "   Level: " << getLevel() << endl;
    cout << "   Race: " << getRace() << endl;
    cout << "   Health: " << getHealth() << endl;
    cout << "   Weapon: " << weapon << endl;
    cout << "   Stamina: " << stamina << endl;
}

int Warrior::attack() {
    int damage; //an integeer variable damage is created and then assigned a random value between 8 - 12 so that each time a warrior attacks, a value of damage in said range is applied to the opponent
    damage = rand() % 5 + 8;
    return damage;
}

string Warrior::pointType() {
    string type = "stamina"; //this function returns "stamina" because it is a warrior object. I can use this function's return value to output a string specific to the character type while still calling the function through a character pointer. 
    return type;
}
