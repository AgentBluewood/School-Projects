//
//  main.cpp
//  Homework 1 - Threads
//
//  Created by Dylan Hilton on 2/13/22.
//

#include <iostream>
#include <string>
#include <cmath>
#include <pthread.h>
#include <map>

struct message { //struct meant to handle all variables related to the necessary components of the compressed message
    int *fixedLength;
    int *numSymbols;
    char letter;
    int translation;
    int frequency;
    std::string binary;
    std::string *encodedMessage;
};

struct deconstruct { //struct used solely for the purpose of decompressing my message
    std::map<std::string, char> *dictionary;
    std::string storage;
    char result;
};

std::string decToBin(int convert, int size) { //function takes in decimal number and the amount of bits to convert number to in binary
    std::string temp[50];
    std::string result = "";
    int fill = 0;
    
    while (convert != 0) { //each look takes the remainder of the decimal number I wish to convert. If the remainder is 0, outputs a 0 at end of binary number, and 1 otherwise
        temp[fill] = (convert % 2 == 0 ? "0" : "1");
        convert /= 2;
        fill++;
    }
    
    while (fill < size) { //fills in front of binary number with zeros if the conversion is less than the bits desired
        temp[fill] = "0";
        fill++;
    }
    
    
    for (int y = size; y >= 0; y--) { //constructs the binary number by adding strings together from the end to the beginning
        result = result + temp[y];
    }
    
    return result; //returns the binary number created
}

int getInput(message info[]) { //function meant to populate my array of structs and return value of fixed binary size
    std::string temp, temp2, holder;
    int fixed;
    int symbols = *info[0].numSymbols;
    int largest = 0;
    
    for (int i = 0; i < symbols; i++) {
        getline(std::cin, temp); //reads each line from file into
        
        info[i].letter = temp[0]; //stores the letter necessary for translation in the struct array
        if (temp.length() > 3) { //for one digit numbers, stores the decimal value into the struct by subracting the ASCII value 48 from the character. For 2 digit numbers, takes a substring then uses stoi() function to turn string into int and store in struct
            temp2 = temp.substr(2,2);
            info[i].translation = stoi(temp2);
        } else {
            info[i].translation = temp[2] - 48;
        }
        
        if (info[i].translation > largest) { //updates the value of the largest integer found
            largest = info[i].translation;
        }
    }
    
    fixed = ceil(log2(largest + 1)); //determines and returns the number of bits in binary translation using the largest number provided
    return fixed;
}

void *analyze (void *voidPTR) { //function meant to determine the binary representation of each digit and the frequency of each letter
    std::string temp;
    struct message *messagePTR = (message *) voidPTR;
    
    messagePTR->binary = decToBin(messagePTR->translation, *messagePTR->fixedLength); //uses my decToBin function to convert each integer given to binary
    
    for (int pos = 0; (*messagePTR->encodedMessage).length() - pos >= *messagePTR->fixedLength; pos = pos + *messagePTR->fixedLength) { //traverses the encoded message in intervals the same size as each binary number has bits. Loop continues as long as there are more characters to traverse then the size of each binary digit
        temp = (*messagePTR->encodedMessage).substr(pos, *messagePTR->fixedLength); //stores each interval of binary digits in string and counts the frequency of the digits
        if (messagePTR->binary == temp) {
            messagePTR->frequency++;
        }
    }
    return nullptr;
}

void *decompress (void *voidPTR) { //function to decompress each letter in the coded message
    struct deconstruct *deconstructPTR = (deconstruct *) voidPTR;
    
    auto define = (*deconstructPTR->dictionary).find(deconstructPTR->storage); //defines a map iterator variable with keyword auto to describe the type, then uses the map's find function to pass the binary code and locate the corresponsding character
    deconstructPTR->result = define->second; //character stored in result
    
    return nullptr;
}

int main() {
    freopen("input3.txt", "r", stdin);
    
    int numSymbols; //defines variables necessary to get input and decode message. Stores amount of lines in numSymbols
    int totalCharacters = 0;
    std::string temp;
    std::cin >> numSymbols;
    std::cin.ignore();
    
    struct message *encoded = new message[numSymbols]; //dynamic creation of struct array and pthread_t array
    pthread_t *tid = new pthread_t[numSymbols];
    
    for (int i = 0; i < numSymbols; i++) { //sets frequency to 0 and stores a reference to numSymbols in every element of the struct array so the threads can access them
        encoded[i].frequency = 0;
        encoded[i].numSymbols = &numSymbols;
    }
    
    int size = getInput(encoded); //populates the input from file and stores size of fixed length to add to each element in struct array
    getline(std::cin, temp); //gets encoded message to provide as reference to each element
    
    for (int i = 0; i < numSymbols; i++) { //first set of threads created to find binary representation of each character and their frequency in the compressed messsage
        encoded[i].encodedMessage = &temp;
        encoded[i].fixedLength = &size;
        if (pthread_create(&tid[i], nullptr, analyze, &encoded[i])) {
            fprintf(stderr, "Error creating thread\n");
            return 1;
        }
    }
    
    for (int y = 0; y < numSymbols; y++) { //pthread_join of first set of threads
        pthread_join(tid[y], nullptr);
    }
    
    std::cout << "Alphabet:" << std::endl; //outputs the alphabet, which consists of each character, its binary representation, and the frequency in the encoded messge
    for (int j = 0; j < numSymbols; j++) {
        std::cout << "Character: " << encoded[j].letter << ", Code: " << encoded[j].binary << ", Frequency: " << encoded[j].frequency << std::endl;
    }
    std::cout << std::endl;
    
    for (int x = 0; x < numSymbols; x++) { //adds up all frequencies to find total number of characters in message
        totalCharacters = totalCharacters + encoded[x].frequency;
    }
    
    int increments = 0;
    pthread_t *tidSecond = new pthread_t[totalCharacters]; //creation of second pthread_t array and deconstruct struct used to decrypt the message
    struct deconstruct *solver = new deconstruct[totalCharacters];
    
    std::map <std::string, char> placeholder;
    for (int i = 0; i < numSymbols; i++) { //inserts each binary representation and the corresponding character into my placeholder map
        placeholder.insert({encoded[i].binary, encoded[i].letter});
    }
    
    for (int p = 0; p < totalCharacters; p++) {
        solver[p].dictionary = &placeholder; //provides a reference of the placeholder into each dictionary element of the array so it can be accessed in the thread
        solver[p].storage = (*encoded[0].encodedMessage).substr(increments, *encoded[0].fixedLength); //takes substrings of the specified length to decrypt each corresponding character

        if (pthread_create(&tidSecond[p], nullptr, decompress, &solver[p])) { //second set of threads used to decrypt each character in the encoded message
            fprintf(stderr, "Error creating thread 2\n");
            return 1;
        }
        
        increments += *encoded[0].fixedLength; //variable used to increment in intervals of the amount of binary bits each character has
    }

    for (int q = 0; q < totalCharacters; q++) { //pthread_join of second set of threads
        pthread_join(tidSecond[q], nullptr);
    }
    
    std::cout << "Decompressed message: "; //outputs the final decompressed message
    for (int f = 0; f < totalCharacters; f++) {
        std::cout << solver[f].result;
    }
    
    std::cout << std::endl;
    
    delete [] encoded; //delete all dynamically allocated arrays
    delete [] tid;
    delete [] tidSecond;
    delete [] solver;
        
    return 0;
}
