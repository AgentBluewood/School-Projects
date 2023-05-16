#include "BSTree.h"
#include "BSTNode.h"

BSTree::BSTree()
{
	rootNode = nullptr;
}

BSTree::~BSTree()
{
	//implement destructor

}

int countHeight(BSTNode *start)
{
	int retd;
	if (nullptr == start)
	{
		return -1;
	}
	else
	{
		int ld = countHeight(start->getLeftChild());
		int rd = countHeight(start->getRightChild());
		
		return max(ld, rd) + 1;
	}

}



int BSTree::getHeight() const
{
	return countHeight(rootNode);
}


int countNodes(BSTNode* start)
{
	if (nullptr == start)
	{
		return 0;
	}
	else
	{
		return 1 + countNodes(start->getLeftChild()) + countNodes(start->getRightChild());
	}
}

int BSTree::getNumNodes() const
{
	return countNodes(rootNode);
}

void preorder(BSTNode* current, string& path) {
    if (current != nullptr) {
        cout << current->getKey() << " ";
        preorder(current->getLeftChild(), path);
        preorder(current->getRightChild(), path);
    }
}

string BSTree::getRepresentation()
{
	//implement function
    string result = "";
    preorder(rootNode, result);
    return result;
}

BSTNode* BSTree::getNode(string key)
{
	//implement function
    BSTNode* currentNode = rootNode;
    while (currentNode != nullptr) {
        if (key == currentNode->getKey()) {
            return currentNode;
        } else if (key < currentNode->getKey()) {
            currentNode = currentNode->getLeftChild();
        } else {
            currentNode = currentNode->getRightChild();
        }
    }
    
    return nullptr;
}


bool BSTree::addNode(string key)
{
	BSTNode* newNode = new BSTNode(key);
	addNode(newNode);
	return true;
}

bool BSTree::addNode(BSTNode* item)
{
	//implement function
    if (rootNode == nullptr) {
        rootNode = item;
    } else {
        BSTNode* currentNode = rootNode;
        while (currentNode != nullptr) {
            if (strcmp(item->getKey().c_str(), currentNode->getKey().c_str()) < 0) {
                if (currentNode->getLeftChild() == nullptr) {
                    currentNode->setLeftChild(item);
                    currentNode = nullptr;
                } else {
                    currentNode = currentNode->getLeftChild();
                }
            } else {
                if (currentNode->getRightChild() == nullptr) {
                    currentNode->setRightChild(item);
                    currentNode = nullptr;
                } else {
                    currentNode = currentNode->getRightChild();
                }
            }
        }
    }
    return true;
}


