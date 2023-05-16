#ifndef BSTNode_H
#define BSTNode_H

#include <string>
using namespace std;

class BSTNode {
private:
    string NodeKey;
    BSTNode* LeftChild;
    BSTNode* RightChild;

public:
    BSTNode(string key);

    string getKey() const;
    void setKey(const string key);

    void setLeftChild(BSTNode* lc);
    void setRightChild(BSTNode* rc);
    BSTNode* getLeftChild();
    BSTNode* getRightChild();

};
#endif // BSTNode_H
