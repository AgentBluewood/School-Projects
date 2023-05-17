//
//  Character.h
//  Game Battle
//
//  Created by Dylan Hilton on 4/24/21.
//

#include <iostream>
#include <cstdlib>
#include <string>

using namespace std;

#ifndef Character_h
#define Character_h

class Character {
    private:
        string name;
        string race;
        int level;
        int health;
    public:
        void setHealth(int characterHealth); //all basic getter and setter functions used to create a generic character and retrieve said character's values
        void setName(string characterName);
        void setLevel(int characterLevel);
        void setRace(string characterRace);
        int getHealth();
        string getName();
        int getLevel();
        string getRace();
        virtual void printInfo() = 0; //declares three pure virtual functions to allow inheriting classes to configure the code based on the character type
        virtual int attack() = 0;
        virtual string pointType() = 0;
};

#endif /* Character_h */
