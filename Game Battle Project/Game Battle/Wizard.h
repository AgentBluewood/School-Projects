//
//  Wizard.h
//  Game Battle
//
//  Created by Dylan Hilton on 4/24/21.
//

#include "Character.h"

#ifndef Wizard_h
#define Wizard_h

class Wizard : public Character {
    private:
        string spell;
        int mana;
    public:
        Wizard(); //just like warrior, has two constructors to allow for easier creation of a wizard object
        Wizard(string _name, string _race, int _level, int _health, int _mana, string _spell);
        void setSpell(string firstSpell);
        void setMana(int characterMana);
        string getSpell();
        int getMana();
        void printInfo(); //just like warrior, defines the three pure virtual functions declared in character.h
        int attack();
        string pointType();
};

#endif /* Wizard_h */
