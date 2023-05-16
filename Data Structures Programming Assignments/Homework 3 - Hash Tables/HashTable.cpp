#include "HashTable.h"
#include <iostream>

HashTable::HashTable() {
	bucketArray = new HashBucket[10];
	maxBuckets = 10;
}

HashTable::~HashTable() {
	//free memory related to the table
    BucketNode* current;
    BucketNode* temp;
    for (int i = 0; i < 10; i++) {
        if (bucketArray[i].head != nullptr) {
            current = bucketArray[i].head;
            while (current != nullptr) {
                temp = current->prev;
                current = nullptr;
                delete current;
                current = temp;
            }
        }
    }
}

int HashTable::hashFunc(string password) {
	int hashval = 0;
	for (unsigned int i = 0; i < password.size(); i++) {
		hashval = hashval + ((char)password[i]);
	}
	hashval = hashval % 10;
	return hashval;
}

int HashTable::numElementsInBucket(int bucketIndex) {
	//return number of passwords in specified bucket of hash table
    BucketNode* current;
    int numItems = 0;
    
    if (bucketArray[bucketIndex].head == nullptr) {
        return numItems;
    } else {
        current = bucketArray[bucketIndex].head;
        while (current != nullptr) {
            numItems++;
            current = current->next;
        }
        return numItems;
    }
}

void HashTable::addElement(string password, bool actualPassword) {
	//add password to correct bucket in hash table; also, indicate if password was from the actualPassword.txt file or attemptedPassword.txt file
    int key = hashFunc(password);
    BucketNode* newNode = new BucketNode;
    BucketNode* current;
    newNode->password = password;
    newNode->actualPassword = actualPassword;
    
    if (bucketArray[key].head == nullptr) {
        bucketArray[key].head = newNode;
        newNode->next = nullptr;
        newNode->prev = nullptr;
    } else {
        current = bucketArray[key].head;
        while (current->next != nullptr) {
            current = current->next;
        }
        current->next = newNode;
        newNode->prev = current;
        newNode->next = nullptr;
    }
}

void HashTable::removeElements() {
	//print all nodes in buckets consisting of only one element, then delete that element
    for (int i = 0; i < 10; i++) {
        if (numElementsInBucket(i) == 1) {
            cout << bucketArray[i].head->password << " deleted" << endl;
            delete bucketArray[i].head;
            bucketArray[i].head = nullptr;
        }
    }
}

void HashTable::printCollisions() {
	//print all compromised passwords
    BucketNode* current;
    int collisions;
    for (int i = 0; i < 10; i++) {
        collisions = 0;
        if (numElementsInBucket(i) > 1) {
            current = bucketArray[i].head;
            while (current->next != nullptr) {
                collisions++;
                current = current->next;
            }
            if (bucketArray[i].head->actualPassword) {
                cout << bucketArray[i].head->password << ": " << collisions << " collisions" << endl;
            }
        }
    }
}
