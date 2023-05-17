//
//  Archer.hpp
//  Game Battle
//
//  Created by Dylan Hilton on 4/25/21.
//

#include "Character.h"

#ifndef Archer_h
#define Archer_h

class Archer : public Character {
    private:
        string arrowType;
        int energy;
    public:
        Archer(); //just like warrior and wizard, contains two constructors to allow for easier creation of an archer object
        Archer(string _name, string _race, int _level, int _health, int _energy, string _arrowType);
        void setArrowType(string characterArrow);
        void setEnergy(int characterEnergy);
        string getArrowType();
        int getEnergy();
        void printInfo(); //defines the three pure virtual functions declared in character.h
        int attack();
        string pointType();
};

#endif /* Archer_hpp */
