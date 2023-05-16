#ifndef BUCKETNODE_H
#define BUCKETNODE_H

#include <string>

using namespace std;

class BucketNode
{
public:
    BucketNode* next;
    BucketNode* prev;
    string password;
    bool actualPassword;

    BucketNode()
    {
        next = nullptr;
        prev = nullptr;
        password = "";
    }
};

#endif