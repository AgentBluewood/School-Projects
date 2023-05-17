//
//  Warrior.h
//  Game Battle
//
//  Created by Dylan Hilton on 4/24/21.
//

#include "Character.h"

#ifndef Warrior_h
#define Warrior_h

class Warrior : public Character {
    private:
        int stamina;
        string weapon;
    public:
        Warrior(); //declares two constuctors, one without parameters and one with parameters to allow easier creation of a warrior object if need be
        Warrior(string _name, string _race, int _level, int _health, int _stamina, string _weapon);
        void setStamina(int characterStamina);
        void setWeapon(string characterWeapon);
        int getStamina();
        string getWeapon();
        void printInfo(); //this function and the two below are the three pure virtual functions declaredin character.h
        int attack();
        string pointType();
};

#endif /* Warrior_h */
