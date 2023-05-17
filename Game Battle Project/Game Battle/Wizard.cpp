//
//  Wizard.cpp
//  Game Battle
//
//  Created by Dylan Hilton on 4/24/21.
//

#include "Wizard.h"

Wizard::Wizard() {
    setName("Unknown");
    setRace("Unknown");
    setLevel(0);
    setHealth(100);
    mana = 3;
    spell = "None";
}

Wizard::Wizard(string _name, string _race, int _level, int _health, int _mana, string _spell) {
    setName(_name);
    setRace(_race);
    setLevel(_level);
    setHealth(_health);
    mana = _mana;
    spell = _spell;
}

void Wizard::setSpell(string firstSpell) {
    spell = firstSpell;
}

void Wizard::setMana(int characterMana) {
    mana = characterMana;
}

string Wizard::getSpell() {
    return spell;
}

int Wizard::getMana() {
    return mana;
}

void Wizard::printInfo() {
    cout << "Wizard Information:" << endl;
    cout << "   Name: " << getName() << endl;
    cout << "   Level: " << getLevel() << endl;
    cout << "   Race: " << getRace() << endl;
    cout << "   Health: " << getHealth() << endl;
    cout << "   Spell: " << spell << endl;
    cout << "   Mana: " << mana << endl;
}

int Wizard::attack() {
    int damage; //wizards also output a random amount of damage between 8 - 12
    damage = rand() % 5 + 8;
    return damage;
}

string Wizard::pointType() {
    string type = "mana"; //this function returns "mana" so that when my character pointer points to a wizard object, I can return "mana" instead of "stamina" or "energy"
    return type;
}
