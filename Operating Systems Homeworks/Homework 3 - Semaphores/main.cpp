//
//  main.cpp
//  Homework 3 - Semaphores
//
//  Created by Dylan Hilton on 4/25/22.
//

#include <pthread.h>
#include <iostream>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>
#include <cmath>
#include <map>
#include <vector>

struct message { //struct meant to handle all variables related to the necessary components of the compressed message
    int *numSymbols;
    char letter;
    int decimalValue;
};

struct constantFeatures { //struct used to keep track of unchanging elements of the program such as the binary code and the fixed length bits. Also used to pass information from main thread to child thread using mutex semaphores
    int numSymbols;
    std::string encodedMessage;
    int fixedLength;
    char character;
    int tensValue;
    pthread_mutex_t* bsem;
    pthread_cond_t* waitTurn;
    int* threadTurn;
    int threadNumber;
};

struct deconstruct { //struct used to handle the decoding of the binary message using mutex semaphores
    std::map<std::string, char> dictionary;
    std::string bitSequence;
    pthread_mutex_t* semB;
    pthread_cond_t* turnWait;
    int* turn;
    int number;
    std::string* final;
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
            info[i].decimalValue = stoi(temp2);
        } else {
            info[i].decimalValue = temp[2] - 48;
        }
        
        if (info[i].decimalValue > largest) { //updates the value of the largest integer found
            largest = info[i].decimalValue;
        }
    }
    
    fixed = ceil(log2(largest + 1)); //determines and returns the number of bits in binary translation using the largest number provided
    return fixed;
}

void *analyze (void *voidPTR) { //function meant to determine the binary representation of each digit and the frequency of each letter
    constantFeatures constantFeaturesStruct = *(constantFeatures*) voidPTR;
    pthread_mutex_unlock(constantFeaturesStruct.bsem); //ends critical section after copying information from main thread to local variable
    
    std::string binary = decToBin(constantFeaturesStruct.tensValue, constantFeaturesStruct.fixedLength); //uses decToBin function to convert given decimal value to binary
    int frequency = 0;
    
    for (int pos = 0; (constantFeaturesStruct.encodedMessage).length() - pos >= constantFeaturesStruct.fixedLength; pos = pos + constantFeaturesStruct.fixedLength) { //traverses the encoded message in intervals the same size as each binary number has bits. Loop continues as long as there are more characters to traverse then the size of each binary digit
        std::string temp = (constantFeaturesStruct.encodedMessage).substr(pos, constantFeaturesStruct.fixedLength); //stores each interval of binary digits in string and counts the frequency of the digits
        if (binary == temp) {
            frequency++;
        }
    }
    
    pthread_mutex_lock(constantFeaturesStruct.bsem); //starts a critical section to make sure the current thread is allowed to print to maintain the correct order
    while (constantFeaturesStruct.threadNumber != *constantFeaturesStruct.threadTurn) {
        pthread_cond_wait(constantFeaturesStruct.waitTurn, constantFeaturesStruct.bsem);
    }
    pthread_mutex_unlock(constantFeaturesStruct.bsem);
    
    std::cout << "Character: " << constantFeaturesStruct.character << ", Code: " << binary << ", Frequency: " << frequency << std::endl;
    
    pthread_mutex_lock(constantFeaturesStruct.bsem); //starts critical section to increment the thread turn and broadcast to any waiting threads
    *constantFeaturesStruct.threadTurn = *constantFeaturesStruct.threadTurn + 1;
    pthread_cond_broadcast(constantFeaturesStruct.waitTurn);
    pthread_mutex_unlock(constantFeaturesStruct.bsem);
    
    return nullptr;
}

void *decompress (void *voidPTR) { //function to decompress each letter in the coded message
    deconstruct deconstructStruct = *(deconstruct*) voidPTR;
    pthread_mutex_unlock(deconstructStruct.semB); //ends critical section after copying information from main thread to local variable
    
    auto define = (deconstructStruct.dictionary).find(deconstructStruct.bitSequence); //defines a map iterator variable with keyword auto to describe the type, then uses the map's find function to pass the binary code and locate the corresponsding character
    char result = define->second;
    
    pthread_mutex_lock(deconstructStruct.semB);
    while (deconstructStruct.number != *deconstructStruct.turn) {
        pthread_cond_wait(deconstructStruct.turnWait, deconstructStruct.semB);
    }
    *deconstructStruct.final = *deconstructStruct.final + result; //adds the corresponding character to the end of a string that contains the decompressed message
    *deconstructStruct.turn = *deconstructStruct.turn + 1;
    pthread_cond_broadcast(deconstructStruct.turnWait);
    pthread_mutex_unlock(deconstructStruct.semB);
    
    return nullptr;
}

int main(int argc, const char * argv[]) {
    freopen("input2.txt", "r", stdin);
    
    static constantFeatures elements; //creates constant features struct and populates numSymbols with input from file
    int totalCharacters;
    std::cin >> elements.numSymbols;
    std::cin.ignore();
    
    struct message *encoded = new message[elements.numSymbols]; //dynamic creation of struct array and pthread_t array
    pthread_t *tid = new pthread_t[elements.numSymbols];
    encoded[0].numSymbols = &elements.numSymbols; //copies numSymbols into first index of struct variable for use in getInput() function
    
    static pthread_mutex_t bsem; //creation and intialization of mutex semaphore and condition variable for first set of threads
    static pthread_cond_t waitTurn;
    pthread_mutex_init(&bsem, NULL);
    pthread_cond_init(&waitTurn, NULL);
    
    elements.bsem = &bsem; //sets the members of the struct to point to the addresses of the mutex semaphores and condition variables created in main
    elements.waitTurn = &waitTurn;
    int turn = 0;
    elements.threadTurn = &turn;
    
    elements.fixedLength = getInput(encoded); //populates the input from file and stores size of fixed length to add to each element in struct array
    getline(std::cin, elements.encodedMessage); //gets encoded message to provide as reference to element struct
    
    std::cout << "Alphabet: " << std::endl;
    for (int i = 0; i < elements.numSymbols; i++) { //first set of threads created to find binary representation of each character and their frequency in the compressed messsage
        pthread_mutex_lock(elements.bsem); //starts critical section and only allows the thread whose turn it is to enter child thread
        
        elements.character = encoded[i].letter; //copies variable from struct to member variables of elements struct
        elements.tensValue = encoded[i].decimalValue;
        elements.threadNumber = i;
        
        if (pthread_create(&tid[i], nullptr, analyze, &elements)) { //first set of threads to determine binary value and frequency
            fprintf(stderr, "Error creating thread\n");
            return 1;
        }
    }
    
    for (int y = 0; y < elements.numSymbols; y++) { //pthread_join of first set of threads
        pthread_join(tid[y], nullptr);
    }
    
   totalCharacters = elements.encodedMessage.length() / elements.fixedLength; //calculates total number of characters by dividing the length of the binary code by the number of fixed length bits
    
    int increments = 0; //variable used to determine starting index of string element to take substrings
    static deconstruct decryption;
    pthread_t *tidSecond = new pthread_t[totalCharacters]; //creation of second pthread_t array and deconstruct struct used to decrypt the message
    
    static pthread_mutex_t semB; //creation and intialization of mutex semaphore and condition variable for second set of threads
    static pthread_cond_t turnWait;
    pthread_mutex_init(&semB, NULL);
    pthread_cond_init(&turnWait, NULL);
    
    decryption.semB = &semB; //sets the members of the struct to point to the addresses of the mutex semaphores and condition variables created in main
    decryption.turnWait = &turnWait;
    int turn2 = 0;
    decryption.turn = &turn2;
    std::string final = "";
    decryption.final = &final;
    
    for (int i = 0; i < elements.numSymbols; i++) { //inserts each binary representation and the corresponding character into my placeholder map
        decryption.dictionary.insert({decToBin(encoded[i].decimalValue, elements.fixedLength), encoded[i].letter});
    }
    
    for (int p = 0; p < totalCharacters; p++) {
        pthread_mutex_lock(decryption.semB); //starts critical section and only allow the thread whose turn it is to enter child thread
        decryption.bitSequence = elements.encodedMessage.substr(increments, elements.fixedLength); //takes substrings of the specified length to decrypt each corresponding character
        decryption.number = p;
        increments += elements.fixedLength; //variable used to increment in intervals of the amount of binary bits each character has
        
        if (pthread_create(&tidSecond[p], nullptr, decompress, &decryption)) { //second set of threads used to decrypt each character in the encoded message
            fprintf(stderr, "Error creating thread 2\n");
            return 1;
        }
    }
    
    for (int q = 0; q < totalCharacters; q++) { //pthread_join of second set of threads
        pthread_join(tidSecond[q], nullptr);
    }
    
    std::cout << "\nDecompressed message: " << *decryption.final << std::endl; //outputs the final decompressed message
    
    delete [] encoded;
    delete [] tid;
    delete [] tidSecond;
    
    return 0;
}
