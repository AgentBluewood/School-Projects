//
//  main.cpp
//  Game Battle
//
//  Created by Dylan Hilton on 4/24/21.
//

#include <iostream>
#include <cstdlib>
#include "Warrior.h"
#include "Wizard.h"
#include "Archer.h"

using namespace std;

Character* player1; //two pointers that will point to the address of the character type the user wants
Character* player2;
Warrior warrior1, warrior2; //creates two of each class type to give each player the option to use the same character type if desired
Wizard wizard1, wizard2;
Archer archer1, archer2;
bool additionalPoints, additionalDamage, p2additionalPoints, p2additionalDamage; //these variables are used to know what perks to grant characters based on their race and attack choices
bool stopGame = false;

void setPlayer1Character() { //this function is used to set the values of the player1 character. It is called whether the user is playing against the computer or against another player
    int characterChoice = 0;
    int raceChoice = 0;
    int level = 0;
    int weaponChoice = 0;
    bool characterChose = false;
    bool raceChose = false;
    bool weaponChose = false;
    string characterName, race, characterType, characterAbility;
    
    cout << "Player 1, here are your options: " << endl;
    cout << "1: Warrior - A talented and strong who specializes in physical combat" << endl;
    cout << "2: Wizard - A powerful sorcer who possesses the ability to perform magic in battle" << endl;
    cout << "3: Archer - A sharpshooter who is skilled in ranged warfare" << endl;
    
    while (characterChose == false) {
        cout << "Enter the number of your desired character" << endl;
        cin >> characterChoice; //takes user input to use in a switch statement so the user can select their character
        cout << endl;
        switch(characterChoice) {
            case 1: {
                characterChose = true; //user entered a valid input, so the while loop can complete and the code can move to the next step in the character creation process
                player1 = &warrior1; //pointer set to the address of the first warrior.
                cout << "Player 1 chooses a warrior!" << endl;
                race = "stamina"; //this variable is used later to match the type of points the character uses to the character the user selected (i.e warriors use stamina, wizards use mana, etc.)
                characterType = "warrior"; //variable is used later to know what function needs to be called to set the character's abilities (i.e warriors need to set weapon, wizards need to set spell, etc.)
                characterAbility = "weapon"; //similar to the race variable, used to accurately match the character type and their ability
                break;
            }
            case 2: {
                characterChose = true;
                player1 = &wizard1;
                cout << "Player 1 chooses a wizard!" << endl;
                race = "mana";
                characterType = "wizard";
                characterAbility = "spell";
                break;
            }
            case 3: {
                characterChose = true;
                player1 = &archer1;
                cout << "Player 1 chooses an archer!" << endl;
                race = "energy";
                characterType = "archer";
                characterAbility = "arrow type";
                break;
            }
            default:
                cout << "Invalid character choice, select again!" << endl; //tells the user they entered an invalid value and does not change the bool characterChose so that the loop will repeat and the user will be forced to choose again
                break;
        }
    }
    
    cout << "Name your character (One word names only)!" << endl;
    cin >> characterName; //gets user input to set the character name, sets the character name to whatever the input was, then print its
    player1->setName(characterName);
    cout << endl;
    cout << "Player 1 is named " << player1->getName() << endl;
    
    cout << "Choose a race for your character" << endl;
    cout << "1: Elf - A sneaky creature who gains 3 " << race << " points per round but only has 75 health" << endl;
    cout << "2: Orc - A brute who has 150 health but only gains 2 " << race << " points per round" << endl;
    
    while(raceChose == false) {
        cout << "Enter the number of your desired race" << endl;
        cin >> raceChoice;
        cout << endl;
        switch(raceChoice) {
            case 1:
                cout << "Player 1 chooses an elf!" << endl;
                player1->setRace("Elf"); //sets the race based of the user input
                raceChose = true; //user entered a valid input, so the while loop can complete and the code can move to the next step in the character creation process
                player1->setHealth(75); //sets the health based on the user choice of race
                additionalPoints = true; //sets the bool value to true so the program knows to add 3 mana/stamina/energy after each turn instead of two
                break;
            case 2:
                cout << "Player 1 chose an orc!" << endl;
                player1->setRace("Orc");
                raceChose = true;
                player1->setHealth(125);
                additionalPoints = false;
                break;
            default:
                cout << "Invalid race selection, try again!" << endl; //tells the user they entered an invalid value and does not change the bool raceChose so that the loop will repeat and the user will be forced to choose again
                break;
        }
    }
    
    level = rand() % 5 + 1; //assigns the integer level with a random value between 1 - 5. This value will be added to the user's attack damage to ensure that higher level characters do more damage. The value is randomized to promote fairness between users.
    player1->setLevel(level);
    
    cout << "Choose your " << characterType << "'s " << characterAbility << endl;  //the characterType and characterAbility variables were set earlier so that this statement will be more specific to the character type chosen by the user
    if (characterType == "warrior") { //characterType variable used again to determine which functions to call depending on character type, as stated previously. This code repeats twice more in similar fashion for the wizard and archer character types
        cout << "1: Dual Axes - Two powerful but lightweight axes that guarantee an extra 3 damage to each of your attacks. Deals between 11 and 15 damage" << endl;
        cout << "2: Broadsword - A double-edged sword that grants a 50% chance of an extra 5 damage to your attacks. Deals between 8 and 12 damage with a 50% chance of dealing between 13 and 17 damage" << endl;
        
        while (weaponChose == false) {
            cout << "Enter the number of your desired weapon" << endl;
            cin >> weaponChoice; //gets the user's input to determine what weapon to select for the given character
            cout << endl;
            switch(weaponChoice) {
                case 1:
                    cout << "Player 1 chooses dual axes for their warrior!" << endl;
                    additionalDamage = true; //sets the bool value to true so the program knows to always add 3 to the damage done by the given character
                    weaponChose = true; //user entered a valid input, so the while loop can complete and the code can move to the next step in the character creation process
                    warrior1.setWeapon("Dual Axes"); //sets the weapon based of the user input
                    break;
                case 2:
                    cout << "Player 1 chooses a broadsword for their warrior!" << endl;
                    additionalDamage = false; //sets the bool value to false so the program knows to give a 50% chance of adding 5 damage to the user's attack
                    weaponChose = true;
                    warrior1.setWeapon("Broadsword");
                    break;
                default:
                    cout << "Invalid wepaon selection, try again!" << endl; //tells the user they entered an invalid value and does not change the bool weaponChose so that the loop will repeat and the user will be forced to choose again
                    break;
            }
        }
    } else if (characterType == "wizard") { //repetition of the previous block of code, except for wizard characters instead of warriors
        cout << "1: Magma Fireball - A powerful blast of heat that guarantees an extra 3 damage to each of your attacks. Deals between 11 and 15 damage" << endl;
        cout << "2: Explosive Lightning - A quick and stunning attack that grants a 50% chance of an extra 5 damage to your attacks. Deals between 8 and 12 damage with a 50% chance of dealing between 13 and 17 damage" << endl;
        
        while (weaponChose == false) {
            cout << "Enter the number of your desired spell" << endl;
            cin >> weaponChoice;
            cout << endl;
            switch(weaponChoice) {
                case 1:
                    cout << "Player 1 chooses magma fireball for their wizard!" << endl;
                    additionalDamage = true;
                    weaponChose = true;
                    wizard1.setSpell("Magma Fireball");
                    break;
                case 2:
                    cout << "Player 1 chooses explosive lightning for their wizard!" << endl;
                    additionalDamage = false;
                    weaponChose = true;
                    wizard1.setSpell("Explosive Lightning");
                    break;
                default:
                    cout << "Invalid spell selection, try again!" << endl;
                    break;
            }
        }
    } else if (characterType == "archer") { //repetition of the previous block code, except for archer characters instead of wizards
        cout << "1: Ice coated - Freezing cold, frostbite arrows that guarantee an extra 3 damage to each of your attacks. Deals between 11 and 15 damage" << endl;
        cout << "2: Poison Tip - Sharp arrows coated in lethal poison that grant a 50% chance of an extra 5 damage to your attacks. Deals between 8 and 12 damage with a 50% chance of dealing between 13 and 17 damage" << endl;
        
        while (weaponChose == false) {
            cout << "Enter the number of your desired arrow type" << endl;
            cin >> weaponChoice;
            cout << endl;
            switch(weaponChoice) {
                case 1:
                    cout << "Player 1 chooses ice coated arrows for their archer!" << endl;
                    additionalDamage = true;
                    weaponChose = true;
                    archer1.setArrowType("Ice Coated");
                    break;
                case 2:
                    cout << "Player 1 chooses poison tipped arrows for their archer!" << endl;
                    additionalDamage = false;
                    weaponChose = true;
                    archer1.setArrowType("Poison Tipped");
                    break;
                default:
                    cout << "Invalid spell selection, try again!" << endl;
                    break;
            }
        }
    }
    
    cout << "Player 1's Character is fully created!" << endl;
    player1->printInfo(); //after the character has been assigned all the necessary stats, the program prints all of the character's info
}

void setPlayer2Character() { //this function is used if the user chooses to play against another person. The entire function is a mirror image of the previous function setPlayer1Character(), except it sets all the values for player2 instead of player1
    int characterChoice = 0;
    int raceChoice = 0;
    int level = 0;
    int weaponChoice = 0;
    bool characterChose = false;
    bool raceChose = false;
    bool weaponChose = false;
    string characterName, race, characterType, characterAbility;
    
    cout << endl;
    cout << "Player 2, here are your options: " << endl;
    cout << "1: Warrior - A talented and strong who specializes in physical combat" << endl;
    cout << "2: Wizard - A powerful sorcer who possesses the ability to perform magic in battle" << endl;
    cout << "3: Archer - A sharpshooter who is skilled in ranged warfare" << endl;
    
    while (characterChose == false) {
        cout << "Enter the number of your desired character" << endl;
        cin >> characterChoice;
        cout << endl;
        switch(characterChoice) {
            case 1: {
                characterChose = true;
                player2 = &warrior2;
                cout << "Player 2 chooses a warrior!" << endl;
                race = "stamina";
                characterType = "warrior";
                characterAbility = "weapon";
                break;
            }
            case 2: {
                characterChose = true;
                player2 = &wizard2;
                cout << "Player 2 chooses a wizard!" << endl;
                race = "mana";
                characterType = "wizard";
                characterAbility = "spell";
                break;
            }
            case 3: {
                characterChose = true;
                player2 = &archer2;
                cout << "Player 2 chooses an archer!" << endl;
                race = "energy";
                characterType = "archer";
                characterAbility = "arrow type";
                break;
            }
            default:
                cout << "Invalid character choice, select again!" << endl;
                break;
        }
    }
    
    cout << "Name your character (One word names only)!" << endl;
    cin >> characterName;
    player2->setName(characterName);
    cout << endl;
    cout << "Player 2 is named " << player2->getName() << endl;
    
    cout << "Choose a race for your character" << endl;
    cout << "1: Elf - A sneaky creature who gains 3 " << race << " points per round but only has 75 health" << endl;
    cout << "2: Orc - A brute who has 150 health but only gains 2 " << race << " points per round" << endl;
    
    while(raceChose == false) {
        cout << "Enter the number of your desired race" << endl;
        cin >> raceChoice;
        cout << endl;
        switch(raceChoice) {
            case 1:
                cout << "Player 2 chooses an elf!" << endl;
                player2->setRace("Elf");
                raceChose = true;
                player2->setHealth(75);
                p2additionalPoints = true;
                break;
            case 2:
                cout << "Player 2 chose an orc!" << endl;
                player2->setRace("Orc");
                raceChose = true;
                player2->setHealth(125);
                p2additionalPoints = false;
                break;
            default:
                cout << "Invalid race selection, try again!" << endl;
                break;
        }
    }
    
    level = rand() % 5 + 1;
    player2->setLevel(level);
    
    cout << "Choose your " << characterType << "'s " << characterAbility << endl;
    if (characterType == "warrior") {
        cout << "1: Dual Axes - Two powerful but lightweight axes that guarantee an extra 3 damage to each of your attacks. Deals between 11 and 15 damage" << endl;
        cout << "2: Broadsword - A double-edged sword that grants a 50% chance of an extra 5 damage to your attacks. Deals between 8 and 12 damage with a 50% chance of dealing between 13 and 17 damage" << endl;
        
        while (weaponChose == false) {
            cout << "Enter the number of your desired weapon" << endl;
            cin >> weaponChoice;
            cout << endl;
            switch(weaponChoice) {
                case 1:
                    cout << "Player 2 chooses dual axes for their warrior!" << endl;
                    p2additionalDamage = true;
                    weaponChose = true;
                    warrior2.setWeapon("Dual Axes");
                    break;
                case 2:
                    cout << "Player 2 chooses a broadsword for their warrior!" << endl;
                    p2additionalDamage = false;
                    weaponChose = true;
                    warrior2.setWeapon("Broadsword");
                    break;
                default:
                    cout << "Invalid wepaon selection, try again!" << endl;
                    break;
            }
        }
    } else if (characterType == "wizard") {
        cout << "1: Magma Fireball - A powerful blast of heat that guarantees an extra 3 damage to each of your attacks. Deals between 11 and 15 damage" << endl;
        cout << "2: Explosive Lightning - A quick and stunning attack that grants a 50% chance of an extra 5 damage to your attacks. Deals between 8 and 12 damage with a 50% chance of dealing between 13 and 17 damage" << endl;
        
        while (weaponChose == false) {
            cout << "Enter the number of your desired spell" << endl;
            cin >> weaponChoice;
            cout << endl;
            switch(weaponChoice) {
                case 1:
                    cout << "Player 2 chooses magma fireball for their wizard!" << endl;
                    p2additionalDamage = true;
                    weaponChose = true;
                    wizard2.setSpell("Magma Fireball");
                    break;
                case 2:
                    cout << "Player 2 chooses explosive lightning for their wizard!" << endl;
                    p2additionalDamage = false;
                    weaponChose = true;
                    wizard2.setSpell("Explosive Lightning");
                    break;
                default:
                    cout << "Invalid spell selection, try again!" << endl;
                    break;
            }
        }
    } else if (characterType == "archer") {
        cout << "1: Ice coated - Freezing cold, frostbite arrows that guarantee an extra 3 damage to each of your attacks. Deals between 11 and 15 damage" << endl;
        cout << "2: Poison Tip - Sharp arrows coated in lethal poison that grant a 50% chance of an extra 5 damage to your attacks. Deals between 8 and 12 damage with a 50% chance of dealing between 13 and 17 damage" << endl;
        
        while (weaponChose == false) {
            cout << "Enter the number of your desired arrow type" << endl;
            cin >> weaponChoice;
            cout << endl;
            switch(weaponChoice) {
                case 1:
                    cout << "Player 2 chooses ice coated arrows for their archer!" << endl;
                    p2additionalDamage = true;
                    weaponChose = true;
                    archer2.setArrowType("Ice Coated");
                    break;
                case 2:
                    cout << "Player 2 chooses poison tipped arrows for their archer!" << endl;
                    p2additionalDamage = false;
                    weaponChose = true;
                    archer2.setArrowType("Poison Tipped");
                    break;
                default:
                    cout << "Invalid spell selection, try again!" << endl;
                    break;
            }
        }
    }
    
    cout << "Player 2's Character is fully created!" << endl;
    player2->printInfo();
}

void setComputer() { //this function is used if the user chooses to play against the computer
    int character, level, race, weapon;
    
    character = rand() % 3; //these 4 variables are randomized and used at different steps of the character creation process for the computer. This ensures the computer is a randomly generated opponent each time the user chooses to play against the computer
    level = rand() % 5 + 1;
    race = rand() % 2;
    weapon = rand() % 2;
    
    switch(character) { //the random character variable first assigns the computer a character type based on the generated value. 0 generates a warrior, 1 a wizard, and 2 an archer
        case 0:
            player2 = &warrior2;
            switch(weapon) { //within each character type creation section of the switch statement is another switch statement that uses the randomly generated value of weapon to determine which weapon to give the computer
                case 0:
                    warrior2.setWeapon("Dual Axes");
                    p2additionalDamage = true; //based on the weapon assigned to the computer, the program will make this bool variable true or false. When true, this bool grants 3 additional damage to each attack. When false, there is a 50% chance of an additional 5 damage to each attack. The weapons of the computer have the same perks as the weapons of the actual players.
                    break;
                case 1:
                    warrior2.setWeapon("Broadsword");
                    p2additionalDamage = false;
                    break;
                default:
                    cout << "Coding error, rewrite" << endl; //if this line prints, it is tellig me that I accidentally coded the random variables wrong because i am getting a value that is not 0 or 1, and therefore I need to adjust my code
                    break;
            }
            break;
        case 1: //the process above repeats, but this time for a wizard instead of a warrior
            player2 = &wizard2;
            switch(weapon) {
                case 0:
                    wizard2.setSpell("Magma Fireball");
                    p2additionalDamage = true;
                    break;
                case 1:
                    wizard2.setSpell("Explosive Lightning");
                    p2additionalDamage = false;
                    break;
                default:
                    cout << "Coding error, rewrite" << endl;
                    break;
            }
            break;
        case 2: //the process above repeats, but this time for an archer instead of a wizard
            player2 = &archer2;
            switch(weapon) {
                case 0:
                    archer2.setArrowType("Ice Coated");
                    p2additionalDamage = true;
                    break;
                case 1:
                    archer2.setArrowType("Poison Tipped");
                    p2additionalDamage = false;
                    break;
                default:
                    cout << "Coding error, rewrite" << endl;
                    break;
            }
            break;
        default:
            cout << "Coding error, rewrite" << endl;
            break;
    }
    
    switch(race) { //the randomized value stored in the variable race is used to select the race of the computer's character
        case 0:
            player2->setRace("Elf"); //if race = 0, the computer's race is an elf
            p2additionalPoints = true; //this bool variables tells the program to add 3 mana/stamina/energy to the character after each turn since it is true
            player2->setHealth(75); //elf characters only have 75 health, so the program sets the computer's health to 75
            break;
        case 1:
            player2->setRace("Orc"); //if race = 1
            p2additionalPoints = false; //this bool variables tells the program to add 2 mana/stamina/energy to the character after each turn since it is false
            player2->setHealth(125); //orc character have 125 health, so the program sets the computer's health to 125
            break;
        default:
            cout << "Coding error, rewrite" << endl; //any other value stored in race other than 0 or 1 means I have made a coding error and need to rewrite my code
            break;

    }
    
    player2->setName("AI"); //sets the computer's name to AI
    player2->setLevel(level); //sets the computer's level to the randomized value of the level variable
    
    cout << endl << "Random generation of AI opponent completed" << endl;
    player2->printInfo(); //prints the information of the computer's charcter after all values are set
}

void playerAgainstComputer () {
    int p1Strength = 0; //since some characters have mana, some have stamina, and some have energy, a generic variable called strength is created for each character to store the value that is in the mana/stamina/energy category
    int p2Strength = 0;
    
    if (player1->pointType() == "stamina") { //based on the value returned by the function pointType(), the program will know whether the character the player selected is a warrior, wizard or archer, and can set the value of p1Strength to the respective point type's value (e.g pointType = stamina, know we need warriors stamina value)
        p1Strength = warrior1.getStamina();
    } else if (player1->pointType() == "mana") { //process above repeats except for wizards
        p1Strength = wizard1.getMana();
    } else if (player1->pointType() == "energy") { //process above repeats except for archers
        p1Strength = archer1.getEnergy();
    }
    
    if (player2->pointType() == "stamina") { //entire if block above repeats except to set the value of p2Strength for the computer
        p2Strength = warrior2.getStamina();
    } else if (player2->pointType() == "mana") {
        p2Strength = wizard2.getMana();
    } else if (player2->pointType() == "energy") {
        p2Strength = archer2.getEnergy();
    }
    int attack, health, chance, computerHealth, computerChance;
    int damage = 0;
    int computerDamage = 0;
    bool attackChose;
    
    cout << endl << "Rules: You are playing against the computer. The game will end when either your character or the computer's character has no remaining health. Each character was randomly assigned a level between 1 and 5. The level of your character will add that amount of damage to your attacks (e.g. A level 3 character has +3 attack damage). When it is your turn, you will have two options:" << endl << endl;
    cout << "1: Perform a regular attack that costs 1 mana/stamina/energy to cast" << endl;
    cout << "2: Perform a super attack that doubles your damage but costs 5 mana/stamina/energy to cast" << endl << endl;
    cout << "All characters start with 3 mana/stamina/energy. Now, it is time to fight!" << endl;
    
    while (player1->getHealth() > 0 && player2->getHealth() > 0) { //this loop will continue until either character has died
        attackChose = false; //sets this bool value to false at the beginning of each loop so that the user is forced to entire a valid value in the following switch statement before the program can move on
        while (attackChose == false) {
            cout << "Type 1 to perform a regular attack or 2 to perform a super attack" << endl;
            cin >> attack; //gets the user input to determine whether to perform a normal or a super attack
            cout << endl;
            switch(attack) {
                case 1:
                    if (additionalDamage == true) { //the global variable additionalDamage comes into play here. Since it is true, it will execute a block of code that will add three damage to the value of the user's attack
                        damage = player1->attack() + 3 + player1->getLevel(); //the integer variable damage is assigned with the player's attack value, plus 3 since additionalDamage is true, plus the level of the player's character
                        health = player2->getHealth() - damage; //the variable health is set to the opponent's health minus the damage just dealt by the player
                        player2->setHealth(health); //the opponent's health is set to value of the variable health from the previous line
                    } else if (additionalDamage == false) { //since additionalDamage is false, there will be a 50% chance of an extra 5 damage being added to the attack
                        chance = rand() % 2; //the integer variable chance is assigned with the value 0 or 1.
                        if (chance == 0) { //since chance = 0, the player will be granted an extra 5 damage to their attack
                            damage = player1->attack() + 5 + player1->getLevel(); //the variable damage is set with the value of the player's attack, plus 5 since chance = 0, plus the player's level
                            health = player2->getHealth() - damage; //the integer variable health is set to the opponent's health minus the variable damage from the previous line
                            player2->setHealth(health); //the opponent's health is set to the value of the variable health from the previous line
                        } else if (chance == 1) { //since chance = 1, the player will not be granted any additional damage
                            damage = player1->attack() + player1->getLevel(); //damage is set equal to the player's attack value plus the player's level
                            health = player2->getHealth() - damage; //the next two lines follow the same pattern as the previous two code blocks last two lines
                            player2->setHealth(health);
                        }
                    }
                    attackChose = true; //bool value is set to true, meaning a valid input was given and the loop can continue
                    p1Strength = p1Strength - 1; //player1 loses one mana/energy/stamina for using a regular attack
                    break;
                case 2: //this code block follows the same pattern as the first case in the switch statement, however it mulitplies the user's attack damage by 2 before adding anything to it for the super attack
                    if (p1Strength >= 5) { //the program first checks whether the user has enough mana/stamina/energy to perform a super attack. If so, the code from case 1 is repeated with the exception of first doubling the attack damage, then adding additional damage points
                        if (additionalDamage == true) {
                            damage = (2 * player1->attack()) + 3 + player1->getLevel();
                            health = player2->getHealth() - damage;
                            player2->setHealth(health);
                        } else if (additionalDamage == false) {
                            chance = rand() % 2;
                            if (chance == 0) {
                                damage = (2 * player1->attack()) + 5 + player1->getLevel();
                                health = player2->getHealth() - damage;
                                player2->setHealth(health);
                            } else if (chance == 1) {
                                damage = (2 * player1->attack()) + player1->getLevel();
                                health = player2->getHealth() - damage;
                                player2->setHealth(health);
                            }
                        }
                    p1Strength = p1Strength - 5; //player1 loses 5 mana/stamina/energy points for performing a super attack
                    attackChose = true; //bool value is set to true, meaning a valid input was given and the loop can continue
                    } else {
                        cout << "Unable to cast your super attack, not enough " << player1->pointType() << ", select again!" << endl; // if the user does not have enough energy/mana/stamina to perform a super attack, the program will tell them and force them to select an option again by not setting the bool value of attackChose to true
                    }
                    break;
                default:
                    cout << "Invalid attack selection, try again!" << endl; //tells the user they made an invalid selection and forces them to choose again by not setting the bool value of attackChose to true
                    break;
            }
        }
        
        if (additionalPoints == true) { //if the bool additionalPoints is true, the user is granted +3 to their mana/stamina/energy
            p1Strength = p1Strength + 3;
        } else if (additionalPoints == false) { //if the bool additionalPoints is false, the user is granted +2 to their mana/stamina/energy
            p1Strength = p1Strength + 2;
        }
        
        cout << "You did " << damage << " damage!" << endl; //tells the user how much damage they did in their previous turn
        cout << "Computer Health: " << player2->getHealth() << ", Your remaining " << player1->pointType() << ": " << p1Strength << endl << endl; // tells the user how much remaining health their opponent has and how much stamina/mana/energy they have
        
        if(player2->getHealth() <= 0) { //checks to see if the oppnent is dead. if they are, the loop exits and player1 is granted the victory
            break;
        }
        
        if(p2Strength >= 5) { //checks if the computer has enough damage to perform a super attack. if it does, the computer will perform a super attack. this code is nearly a copy of the code above for a user, only it lacks a switch statement and a bool value because the computer's actions are limited to whether they have enough power to perform a super attack
            if (p2additionalDamage == true) {
                computerDamage = (2 * player2->attack()) + 3 + player2->getLevel();
                computerHealth = player1->getHealth() - computerDamage;
                player1->setHealth(computerHealth);
            } else if (p2additionalDamage == false) {
                computerChance = rand() % 2;
                if (computerChance == 0) {
                    computerDamage = (2 * player2->attack()) + 5 + player2->getLevel();
                    computerHealth = player1->getHealth() - computerDamage;
                    player1->setHealth(computerHealth);
                } else if (computerChance == 1) {
                    computerDamage = (2 * player2->attack()) + player2->getLevel();
                    computerHealth = player1->getHealth() - computerDamage;
                    player1->setHealth(computerHealth);
                }
            }
            p2Strength = p2Strength - 5;
        } else { //if the computer cannot perform a super attack, a regular attack will be performed
            if (p2additionalDamage == true) {
                computerDamage = player2->attack() + 3 + player2->getLevel();
                computerHealth = player1->getHealth() - computerDamage;
                player1->setHealth(computerHealth);
            } else if (p2additionalDamage == false) {
                computerChance = rand() % 2;
                if (computerChance == 0) {
                    computerDamage = player2->attack() + 5 + player2->getLevel();
                    computerHealth = player1->getHealth() - computerDamage;
                    player1->setHealth(computerHealth);
                } else if (computerChance == 1) {
                    computerDamage = player2->attack() + player2->getLevel();
                    computerHealth = player1->getHealth() - computerDamage;
                    player1->setHealth(computerHealth);
                }
            }
            p2Strength = p2Strength - 1;
        }
        
        if(p2additionalPoints == true) { //if p2additionalPoints is true, the computer is granted 3 mana/stamina/energy points
            p2Strength = p2Strength + 3;
        } else if (p2additionalPoints == false) { //if p2additonalPoints is not true, the computer is granted 2 mana/stamina/energy points
            p2Strength = p2Strength + 2;
        }
        
        cout << "Computer did " << computerDamage << " damage!" << endl; //tells the user how much damage the computer just did
        cout << "Your Health: " << player1->getHealth() << ", Computer's remaining " << player2->pointType() << ": " << p2Strength << endl << endl; //tells the user how much health they have remaining, as well as how much mana/stamina/energy the computer has
        
        if(player1->getHealth() <= 0) { //checks if the computer has killed the player's character. if so, the loop will break and the computer will be granted the victory
            break;
        }
    }
    
    cout << "Game Over!" << endl;
    if (player1->getHealth() <= 0) { //checks which character has no remaining health, and grants the victory to the opposite character
        cout << "The computer won! Better luck next time!" << endl << endl;
    } else if (player2->getHealth() <= 0) {
        cout << "Congratulations! You Won!" << endl << endl;
    }
}

void playerAgainstPlayer() { //this function is similar to the playerAgainstComputer() function, except there are two switch blocks to represent both character's choices
    int p1Strength = 0; //since some characters have mana, some have stamina, and some have energy, a generic variable called strength is created for each character to store the value that is in the mana/stamina/energy category
    int p2Strength = 0;
    
    if (player1->pointType() == "stamina") { //based on the value returned by the function pointType(), the program will know whether the character the player selected is a warrior, wizard or archer, and can set the value of p1Strength to the respective point type's value (e.g pointType = stamina, know we need warriors stamina value)
        p1Strength = warrior1.getStamina();
    } else if (player1->pointType() == "mana") { //process above repeats except for wizards
        p1Strength = wizard1.getMana();
    } else if (player1->pointType() == "energy") { //process above repeats exept for archers
        p1Strength = archer1.getEnergy();
    }
    
    if (player2->pointType() == "stamina") { //entire if block above repeats except to set the value of p2Strength for the second player
        p2Strength = warrior2.getStamina();
    } else if (player2->pointType() == "mana") {
        p2Strength = wizard2.getMana();
    } else if (player2->pointType() == "energy") {
        p2Strength = archer2.getEnergy();
    }

    int p1attack, p2attack, p1health, p1chance, p2health, p2chance;
    int p1damage = 0;
    int p2damage = 0;
    bool p1attackChose, p2attackChose;
    int turn = rand() % 2; //this integer variable is assigned a random number between 0 and 1 so that the player who gets to go first is random. If turn = 0, player 1 goes first, if turn = 1, player 2 goes first
    
    cout << endl << "Rules: You are playing against another player. A random player will be picked to go first. The game will end when either character has no remaining health. Each character was randomly assigned a level between 1 and 5. The level of your character will add that amount of damage to your attacks (e.g. A level 3 character has +3 attack damage). When it is your turn, you will have two options:" << endl << endl;
    cout << "1: Perform a regular attack that costs 1 mana/stamina/energy to cast" << endl;
    cout << "2: Perform a super attack that doubles your damage but costs 5 mana/stamina/energy to cast" << endl << endl;
    cout << "All characters start with 3 mana/stamina/energy. Now, it is time to fight!" << endl << endl;
    
    while (player1->getHealth() > 0 && player2->getHealth() > 0) {
        if (turn == 0) { //this block will execute whenever it is player 1's turn
            cout << "Player 1, it is your turn!" << endl;
            p1attackChose = false; //this bool variable is set to false so that the while loop below repeats until the user enters a valid input
            while (p1attackChose == false) {
                cout << "Type 1 to perform a regular attack or 2 to perform a super attack" << endl;
                cin >> p1attack; //gets the user's input to determine which attack to execute
                cout << endl;
                switch(p1attack) {
                    case 1:
                        if (additionalDamage == true) { //if the user chooses a regular attack and this bool value is true, the program knows to add 3 their damage total
                            p1damage = player1->attack() + 3 + player1->getLevel(); //integer variable is set equal to the character's attack value, plus 3 since additionalDamage is true, plus the character's level
                            p1health = player2->getHealth() - p1damage; //variable is set to the opponent's health minus the damage dealt by the player
                            player2->setHealth(p1health); //the opponent's health is set to the value of the variable above
                        } else if (additionalDamage == false) { //if the user chooses a regular attack and the bool is false, the program knows to grant a 50% chance of 5 additional damage
                            p1chance = rand() % 2; //this integer variable is assigned a random value between 0 and 1
                            if (p1chance == 0) { //if the above integer variable is 0, the user will be granted 5 additional damage
                                p1damage = player1->attack() + 5 + player1->getLevel(); //this block of code is a mirror image of the code from the beginning of the if statement, but 5 additional damage is awarded instead of 3
                                p1health = player2->getHealth() - p1damage;
                                player2->setHealth(p1health);
                            } else if (p1chance == 1) { //if the integer variable is 1, the user will not be awared any additional damage. This block of code is identical to the code from the beginning of the if statement, but no additional damage is awarded
                                p1damage = player1->attack() + player1->getLevel();
                                p1health = player2->getHealth() - p1damage;
                                player2->setHealth(p1health);
                            }
                        }
                        p1attackChose = true; //this bool value is set to true, meaning the user entered a valid input and the while loop can exit
                        p1Strength = p1Strength - 1; //the user loses 1 mana/stamina/energy point for casting a regular attack
                        break;
                    case 2:
                        if (p1Strength >= 5) { //if the user chooses to cast a super attack, the program first checks they have enough mana/energy/stamina to do so. If so, the following code blocks will execute. Everything in this block of code is a mirror image to the above block, except attack damage is first multiplied by 2 before being added to anything
                            if (additionalDamage == true) {
                                p1damage = (2 * player1->attack()) + 3 + player1->getLevel();
                                p1health = player2->getHealth() - p1damage;
                                player2->setHealth(p1health);
                            } else if (additionalDamage == false) {
                                p1chance = rand() % 2;
                                if (p1chance == 0) {
                                    p1damage = (2 * player1->attack()) + 5 + player1->getLevel();
                                    p1health = player2->getHealth() - p1damage;
                                    player2->setHealth(p1health);
                                } else if (p1chance == 1) {
                                    p1damage = (2 * player1->attack()) + player1->getLevel();
                                    p1health = player2->getHealth() - p1damage;
                                    player2->setHealth(p1health);
                                }
                            }
                        p1Strength = p1Strength - 5; //the user loses 5 mana/stamina/energy points for casting a super attack
                        p1attackChose = true;
                        } else { //if the user lacks enough mana/stamina/energy to cast a super attack, the program will tell them and make them select again
                            cout << "Unable to cast your super attack, not enough " << player1->pointType() << ", select again!" << endl;
                        }
                        break;
                    default:
                        cout << "Invalid attack selection, try again!" << endl; //if the user's input was not 1 or 2, they will be told they did not select a valid attack and be forced to choose again
                        break;
                }
            }
            
            if (additionalPoints == true) { //if the bool value is true, the program knows to increase mana/stamina/energy's value by 3
                p1Strength = p1Strength + 3;
            } else if (additionalPoints == false) { //if false, mana/stamina/energy will only be increased by 2
                p1Strength = p1Strength + 2;
            }
            
            cout << "You did " << p1damage << " damage!" << endl; //after choosing an attack, the user will be told how much damage they did, how much health their opponent has remaining, and how much mana/stamina/energy they currently have
            cout << "Player 2 Health: " << player2->getHealth() << ", Player 1 remaining " << player1->pointType() << ": " << p1Strength << endl << endl;
            
            turn = 1; //the value of turn is set to 1 so that when the loop reiterates, it will be player 2's turn
            
            if(player2->getHealth() <= 0) { //statement checks if the opponent has no health remaining, and if so, the loop will break and the game will end
                break;
            }
        } else if (turn == 1) { //this entire block of code that follows is an exact copy of the code below, except everthing applies to player 2 so that they can choose their attack on player 1
            cout << "Player 2, it is your turn!" << endl;
            p2attackChose = false;
            while (p2attackChose == false) {
                cout << "Type 1 to perform a regular attack or 2 to perform a super attack" << endl;
                cin >> p2attack;
                cout << endl;
                switch(p2attack) {
                    case 1:
                        if (p2additionalDamage == true) {
                            p2damage = player2->attack() + 3 + player2->getLevel();
                            p2health = player1->getHealth() - p2damage;
                            player1->setHealth(p2health);
                        } else if (p2additionalDamage == false) {
                            p2chance = rand() % 2;
                            if (p2chance == 0) {
                                p2damage = player2->attack() + 5 + player2->getLevel();
                                p2health = player1->getHealth() - p2damage;
                                player1->setHealth(p2health);
                            } else if (p2chance == 1) {
                                p2damage = player2->attack() + player2->getLevel();
                                p2health = player1->getHealth() - p2damage;
                                player1->setHealth(p2health);
                            }
                        }
                        p2attackChose = true;
                        p2Strength = p2Strength - 1;
                        break;
                    case 2:
                        if (p2Strength >= 5) {
                            if (p2additionalDamage == true) {
                                p2damage = (2 * player2->attack()) + 3 + player2->getLevel();
                                p2health = player1->getHealth() - p2damage;
                                player1->setHealth(p2health);
                            } else if (p2additionalDamage == false) {
                                p2chance = rand() % 2;
                                if (p2chance == 0) {
                                    p2damage = (2 * player2->attack()) + 5 + player2->getLevel();
                                    p2health = player1->getHealth() - p2damage;
                                    player1->setHealth(p2health);
                                } else if (p2chance == 1) {
                                    p2damage = (2 * player2->attack()) + player2->getLevel();
                                    p2health = player1->getHealth() - p2damage;
                                    player1->setHealth(p2health);
                                }
                            }
                        p2Strength = p2Strength - 5;
                        p2attackChose = true;
                        } else {
                            cout << "Unable to cast your super attack, not enough " << player2->pointType() << ", select again!" << endl;
                        }
                        break;
                    default:
                        cout << "Invalid attack selection, try again!" << endl;
                        break;
                }
            }
            
            if (p2additionalPoints == true) {
                p2Strength = p2Strength + 3;
            } else if (p2additionalPoints == false) {
                p2Strength = p2Strength + 2;
            }
            
            cout << "You did " << p2damage << " damage!" << endl;
            cout << "Player 1 Health: " << player1->getHealth() << ", Player 2 remaining " << player2->pointType() << ": " << p2Strength << endl << endl;
            
            turn = 0; //turn is set to 0 so that it will be player 1's turn when the loop reiterates
            
            if(player1->getHealth() <= 0) {
                break;
            }
        }
    }
    
    cout << "Game Over!" << endl;
    if (player1->getHealth() <= 0) { //checks which character has no remaining health, and grants the victory to the opposite character
        cout << "Player 2 Wins! Congratulations " << player2->getName() << "!" << endl << endl;
    } else if (player2->getHealth() <= 0) {
        cout << "Player 1 Wins! Congratulations " << player1->getName() << "!" << endl << endl;
    }
}

void reset() { //this function just resets the global variables to ensure that if the user chooses to play again, everything is reassigned from the beginning and no code is carried over
    Warrior genericWarrior; //the function first declares 3 generic objects for warrior, wizard, and archer. My constructors for these objects will set set the variables of the class to their starting values
    Wizard genericWizard;
    Archer genericArcher;
    
    player1 = nullptr; //the two character pointers are assigned with nullptr so that they do not point to any objects yet
    player2 = nullptr;
    
    warrior1 = genericWarrior; //each global object is set equal to its own respective generic object (i.e warrior objects are set equal to generic warrior, etc.). A shallow copy is performed to set the values in my global objects to those of the generic objects
    warrior2 = genericWarrior;
    wizard1 = genericWizard;
    wizard2 = genericWizard;
    archer1 = genericArcher;
    archer2 = genericArcher;
}

void selectGamemode() {
    int mainOption = 0;
    bool menu = false; //sets the bool value to false so that the following while loop will repeat until the user enters a valid input
    
    cout << "Welcome to Battle Game! Here are your menu options" << endl;
    cout << "1: Play Against the Computer" << endl;
    cout << "2: Play Against Another Player" << endl;
    cout << "3: Exit" << endl;
    
    while(menu == false) {
        cout << "Enter the number of your desired choice" << endl;
        cin >> mainOption; //gets the user's input to determine what game mode they want to play
        cout << endl;
        switch(mainOption) {
            case 1:
                cout << "Playing computer!" << endl;
                menu = true; //user entered a valid input, so set's the bool variable to true to allow the loop to exit, then calls the necessary functions to execute the game mode
                setPlayer1Character();
                setComputer();
                playerAgainstComputer();
                reset();
                break;
            case 2:
                cout << "Playing opponent!" << endl;
                menu = true; //user entered a valid input, so set's the bool variable to true to allow the loop to exit, then calls the necessary functions to execute the game mode
                setPlayer1Character();
                setPlayer2Character();
                playerAgainstPlayer();
                reset();
                break;
            case 3:
                cout << "Exiting!" << endl;
                menu = true; //user entered a valid input, so set's the bool variable to true to allow the loop to exit
                stopGame = true; //sets the global variable stopGame to true to exit the loop in main and end the program
                break;
            default:
                cout << "Unknown entry, try again!" << endl; //user chose an invalid, so the loop reiterates by not changing the value of the bool menu
                break;
        }
    }
}

int main() {
    while (stopGame == false ) { //this loop will repeat until the user chooses to exit the game
        selectGamemode();
    }
    
    cout << "Thanks for playing Battle Game! I hope you enjoyed!" << endl << endl;
    
    return 0;
}
