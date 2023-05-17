//
//  Archer.cpp
//  Game Battle
//
//  Created by Dylan Hilton on 4/25/21.
//

#include "Archer.h"

Archer::Archer() {
    setName("Unknown");
    setRace("Unknown");
    setLevel(0);
    setHealth(100);
    energy = 3;
    arrowType = "None";
}

Archer::Archer(string _name, string _race, int _level, int _health, int _energy, string _arrowType) {
    setName(_name);
    setRace(_race);
    setLevel(_level);
    setHealth(_health);
    energy = _energy;
    arrowType = _arrowType;
}

void Archer::setArrowType(string characterArrow) {
    arrowType = characterArrow;
}

void Archer::setEnergy(int characterEnergy) {
    energy = characterEnergy;
}

string Archer::getArrowType() {
    return arrowType;
}
int Archer::getEnergy() {
    return energy;
}

void Archer::printInfo() {
    cout << "Archer Information:" << endl;
    cout << "   Name: " << getName() << endl;
    cout << "   Level: " << getLevel() << endl;
    cout << "   Race: " << getRace() << endl;
    cout << "   Health: " << getHealth() << endl;
    cout << "   Arrow Type: " << arrowType << endl;
    cout << "   Energy: " << energy << endl;
}

int Archer::attack() {
    int damage; //archer objects also output a random amount of value between 8 - 12
    damage = rand() % 5 + 8;
    return damage;
}

string Archer::pointType() { 
    string type = "energy"; //this function returns "energy" so that when my character pointer points to a wizard object, I can return "energy" instead of "stamina" or "mana"
    return type;
}
