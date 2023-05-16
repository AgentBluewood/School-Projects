#ifndef BSTree_H
#define BSTree_H

#include <string>
#include <iostream>
#include <cstring>
#include <string.h>

#include "BSTNode.h"

using namespace std;

class BSTree
{
private:
	BSTNode* rootNode;

public:
	BSTree();
	~BSTree();

	string getRepresentation();

	bool addNode(string key);
	bool addNode(BSTNode* node);

	int getHeight() const;
	int getNumNodes() const;

	BSTNode* getNode(string key);


};


#endif // BSTree_H

