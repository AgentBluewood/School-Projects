//
//  server.cpp
//  Homework 2 - Interprocess Communication
//
//  Created by Dylan Hilton on 3/22/22.
//

#include <iostream>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <sys/wait.h>
#include <cmath>
#include <map>

struct encryption { //struct used for purpose of holding input from file and the binary representation of the decimal values provided
    char letter;
    int decimal;
    std::string binary;
};

void fireman(int) { //fireman function meant to catch zombie processed
    while(waitpid(-1, NULL, WNOHANG) > 0);
}

std::string decToBin(int convert, int size) { //function takes in decimal number and the amount of bits to convert number to in binary. Code copied from my first programming assignment
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

int getInput(encryption info[], int symbols) { //function meant to populate my array of structs and return value of fixed binary size. Large parts of code copied from my first programming assignment
    std::string temp, intTemp;
    int largest = 0;
    
    for (int i = 0; i < symbols; i++) {
        getline(std::cin, temp); //reads each line from file into temp string
        
        info[i].letter = temp[0]; //stores the letter necessary for translation in the struct array
        if (temp.length() > 3) { //for one digit numbers, stores the decimal value into the struct by subracting the ASCII value 48 from the character. For 2 digit numbers, takes a substring then uses stoi() function to turn string into int and store in struct
            intTemp = temp.substr(2,2);
            info[i].decimal = stoi(intTemp);
        } else {
            info[i].decimal = temp[2] - 48;
        }
        
        if (info[i].decimal > largest) { //updates the value of the largest integer found
            largest = info[i].decimal;
        }
    }
    
    int fixed = ceil(log2(largest + 1)); //determines and returns the number of bits in binary translation using the largest number provided
    return fixed;
}

int main (int argc, const char * argv[]) {
    int numSymbols, numBits; //declaration of variables used to determine number of symbols struct array needs to hold and number of bits to send to client
    char result; //char variable used to hold translation of binary code and send the character to the client
    bool firstRequest = true; //bool used to determine whether request from client is for number of bits or for translation of binary code into a character
    std::map <std::string, char> translator; //creation of map that holds binary code values and the associated character
    std::cin >> numSymbols; //read number of symbols in alphabet from file
    std::cin.ignore();
    
    struct encryption *characteristics = new encryption[numSymbols]; //create dynamic encryption array based on size read from file
    numBits = getInput(characteristics, numSymbols); //populate above struct and get number of bits using getInput() function
    
    for (int i = 0; i < numSymbols; i++) { //converts each decimal number to binary and stores the binary value and associated char in a map
        characteristics[i].binary = decToBin(characteristics[i].decimal, numBits);
        translator.insert({characteristics[i].binary, characteristics[i].letter});
    }
    
    delete [] characteristics;
    
    //start server socket code, got from Dr. Rincon off blackboard
    int sockfd, newsockfd, portno, clilen;
    char buffer[16];
   
    struct sockaddr_in serv_addr, cli_addr;
    int n;
    
    if (argc < 2) {
        printf("ERROR, no port provided");
        exit(1);
    }
    
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) {
        printf("ERROR opening socket");
        exit(1);
    }
       
    bzero((char *) &serv_addr, sizeof(serv_addr));
    portno = atoi(argv[1]);
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons(portno);
    
    if (bind(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0) {
        printf("ERROR on binding");
        exit(1);
    }
    
    listen(sockfd, 20);
    clilen = sizeof(cli_addr); //end of server code copied from Dr. Rincon off blackboard
    
    signal(SIGCHLD, fireman); //use of fireman function to catch zombie processes
    while(true) {
        newsockfd = accept(sockfd, (struct sockaddr *) &cli_addr, (socklen_t *)&clilen); //accepts new connection
        if (fork() == 0) {
            if (newsockfd < 0) {
                printf("ERROR on accept in child process");
                exit(1);
            }
            
            bzero(buffer, 16); //zeros out the  buffer char array and reads into it
            n = read(newsockfd, &buffer, sizeof(buffer));
            if (n < 0) {
                printf("ERROR reading from socket in child process");
                exit(1);
            }
            
            std::string msgStr = std::string(buffer); //converts buffer char array into a string
            
            if (msgStr == "b") { //if string on buffer array is a single "b," the client is requesting bits of fixed length code, so the server will write that to the client
                n = write(newsockfd, &numBits, sizeof(int));
                if (n < 0) {
                    printf("ERROR writing to socket");
                    exit(1);
                }
            } else { //in any other circumstance, the client is requesting translation of a binary code into a char
                auto define = translator.find(msgStr); //defines a map iterator variable with keyword auto to describe the type, then uses the map's find function to pass the binary code and locate the corresponsding character
                result = define->second; //stores resulting char into a char variable and passes that to the client
                
                n = write(newsockfd, &result, sizeof(char));
                if (n < 0) {
                    printf("ERROR writing to socket in child process");
                    exit(1);
                }
            }
            close(newsockfd); //closes new socket, exits child process, and used cin.get() to pause the server between requests
            _exit(0);
        }
        std::cin.get();
    }
    
    close(sockfd); //closes main socket
    return 0;
}
