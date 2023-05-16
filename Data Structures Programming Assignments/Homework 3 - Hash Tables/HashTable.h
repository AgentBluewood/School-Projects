#ifndef HASHTABLE_H
#define HASHTABLE_H

#include "HashBucket.h"
#include <string>

class HashTable {
private:
	int maxBuckets;
	HashBucket* bucketArray;
public:
	HashTable();
	~HashTable();
	int hashFunc(string password);
	int numElementsInBucket(int bucketIndex);
	void addElement(string password, bool actualPassword);
	void removeElements();
	void printCollisions();
};

#endif