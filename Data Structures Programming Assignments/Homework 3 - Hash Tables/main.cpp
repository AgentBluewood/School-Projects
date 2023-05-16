#include <iostream>
#include <string>
#include <fstream>

#include "HashTable.h"

using namespace std;

void readPasswordsFromFile(string filename, HashTable &myHashTable, bool actualPassword) {
	ifstream input(filename);
	string passwordIn;
	if (input.is_open()) {
		while (!input.eof()) {
			input >> passwordIn;
			myHashTable.addElement(passwordIn, actualPassword);
		}
 	}
	else {
		cout << "Error! File not found." << endl;
	}
}

int main(int argc, char** argv) {
	HashTable myHashTable;
	string filename = "actualPasswords.txt";
	readPasswordsFromFile(filename, myHashTable, true);
	filename = "attemptedPasswords.txt";
	readPasswordsFromFile(filename, myHashTable, false);

	cout << "PASSWORDS DELETED FROM HASH TABLE: " << endl;
	myHashTable.removeElements();

	cout << "\nCOMPROMISED PASSWORDS: " << endl;
	myHashTable.printCollisions();

	return 0;
}
