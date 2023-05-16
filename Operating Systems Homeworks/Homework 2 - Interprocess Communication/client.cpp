//
//  main.cpp
//  Homework 2 - Interprocess Communication
//
//  Created by Dylan Hilton on 3/21/22.
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
#include <cstring>

struct binaryToLetter { //struct used to pass information to thread about binary sequence to be translated, resulting char to pass to main thread, and variables used to create a socket in each thread
    std::string binaryLetter;
    char result;
    int* threadPortnumber;
    struct sockaddr_in thread_serv_addr;
    struct hostent *threadServer;
};

void *translator (void *voidPTR) { //function used in each thread meant to send binary sequence to server for translation and store resulting char in memoory accessible to the main thread
    binaryToLetter* binaryToLetterPTR = (binaryToLetter *) voidPTR;
    
    int sockfd, n; //following code copied from Dr. Rincon off blackboard and slightly modified
    char buffer[16];
    
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) {
        printf("ERROR opening socket in thread");
        exit(-1);
    }
    
    bzero((char *) &(binaryToLetterPTR->thread_serv_addr), sizeof(binaryToLetterPTR->thread_serv_addr));
    binaryToLetterPTR->thread_serv_addr.sin_family = AF_INET;
    bcopy((char *)binaryToLetterPTR->threadServer->h_addr, (char *)&(binaryToLetterPTR->thread_serv_addr.sin_addr.s_addr), binaryToLetterPTR->threadServer->h_length);
    binaryToLetterPTR->thread_serv_addr.sin_port = htons(*binaryToLetterPTR->threadPortnumber);
    
    if (connect(sockfd,(struct sockaddr *)&(binaryToLetterPTR->thread_serv_addr),sizeof(binaryToLetterPTR->thread_serv_addr)) < 0) {
        printf("ERROR connecting in thread");
        exit(-1);
    }
    
    bzero(buffer, 16); //zeros out char buffer array and turns string of binary bits into characters to be stored in buffer
    strcpy(buffer, binaryToLetterPTR->binaryLetter.c_str());
    
    n = write(sockfd, &buffer, sizeof(buffer)); //writes the buffer to the server to request bit translation
    if (n < 0) {
        printf("ERROR writing to socket in thread");
        exit(-1);
    }
    
    n = read(sockfd, &binaryToLetterPTR->result, sizeof(char)); //reads the character that the server sends back to the client into a memory location accessed by the main thread
    if (n < 0) {
        printf("ERROR reading from socket in thread");
    }
    
    close(sockfd); //closes socket and finishes function
    return nullptr;
}

int main (int argc, const char * argv[]) {
    std::string binaryCode; //read the provided binary code as input into a string variable
    std::cin >> binaryCode;
    
    int increments = 0;
    int numBits, sockfd, portno, n; //numBits meant to hold number of bits of the fixed-length codes returned by server. other integers necessary for sockets and server communicatin. Code comes from Dr. Rincon's file on blackboard
    struct sockaddr_in serv_addr;
    struct hostent *server;
    
    char buffer[16];
    std::string bitRequest = "b";  //creation of a string and intialized with "b"; this will be used later to signify the client is requesting the bits of fixed length code from serve
    
    if (argc < 3) { //Following code from Dr. Rincon with slight modifications
        printf("Error, not enough arguments provided.");
        exit(-1);
    }
    
    portno = atoi(argv[2]);
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    
    if (sockfd < 0) {
        printf("ERROR opening socket");
        exit(-1);
    }
    
    server = gethostbyname(argv[1]);
    if (server == NULL) {
        printf("ERROR, no such host.");
        exit(-1);
    }
    
    bzero((char *) &serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    bcopy((char *)server->h_addr, (char *)&serv_addr.sin_addr.s_addr, server->h_length);
    serv_addr.sin_port = htons(portno);
    
    if (connect(sockfd,(struct sockaddr *)&serv_addr,sizeof(serv_addr)) < 0) {
        printf("ERROR connecting");
        exit(-1);
    }
    
    bzero(buffer, 16); //zeros out buffer and writes the bitRequest string into the buffer after transforming it into a char array
    strcpy(buffer, bitRequest.c_str());
    
    n = write(sockfd, &buffer, sizeof(buffer)); //sends buffer to server to request number of bits
    if (n < 0) {
        printf("ERROR writing to the socket.");
        exit(-1);
    }
    
    n = read(sockfd, &numBits, sizeof(int)); //writes number of bits of fixed length code into integer variable
    if (n < 0) {
        printf("ERROR reading from the socket.");
        exit(-1);
    }
    close(sockfd); //end of code taken from blackboard
    
    int numCharacters = binaryCode.length() / numBits; //determines the number of characters to be translated by dividing the length of the binary string by the fixed amount of bits
    struct binaryToLetter* decryption = new binaryToLetter[numCharacters]; //creates binaryToLetter struct and p_thread based on value of numCharacters
    pthread_t *tid = new pthread_t[numCharacters];
    
    for (int i = 0; i < numCharacters; i++) {
        decryption[i].binaryLetter = binaryCode.substr(increments, numBits); //for each element in the binaryToLetter decryption array, receives fixed-length segment of binary digits, port number, and server struct
        decryption[i].threadPortnumber = &portno;
        decryption[i].threadServer = server;
        
        if (decryption[i].threadServer == NULL) {
            printf("ERROR, no such host for thread.");
            exit(-1);
        }
        
        if (pthread_create(&tid[i], nullptr, translator, &decryption[i])) { //creates a thread each iteration that sends the decryption element to the translator function
            fprintf(stderr, "Error creating thread 2\n");
            return 1;
        }
        increments += numBits; //increases increments by value stored in numBits each iteration so that the next segment of binary digits can be received
    }
    
    for (int j = 0; j < numCharacters; j++) { //joins the p_threads
        pthread_join(tid[j], nullptr);
    }
    
    std::cout << "Decompressed message: "; //outputs the final decompressed message
    for (int f = 0; f < numCharacters; f++) {
        std::cout << decryption[f].result;
    }
    
    delete [] decryption;
    delete [] tid;
    
    return 0;
}
