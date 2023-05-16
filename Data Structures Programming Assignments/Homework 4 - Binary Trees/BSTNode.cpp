#include <iostream>
#include "BSTNode.h"



BSTNode::BSTNode(string key)
{
    NodeKey = key;
    LeftChild = nullptr;
    RightChild = nullptr;
}

string BSTNode::getKey() const
{
    return NodeKey;
}

void BSTNode::setKey(string key)
{
    NodeKey = key;
}

void BSTNode::setLeftChild(BSTNode* lc)
{
    LeftChild = lc;
}

void BSTNode::setRightChild(BSTNode* rc)
{
    RightChild = rc;
}

BSTNode* BSTNode::getLeftChild()
{
    return LeftChild;
}

BSTNode* BSTNode::getRightChild()
{
    return RightChild;
}
