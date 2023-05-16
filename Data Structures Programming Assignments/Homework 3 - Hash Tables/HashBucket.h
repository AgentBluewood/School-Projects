#ifndef HASHBUCKET_H
#define HASHBUCKET_H

#include "BucketNode.h"

class HashBucket
{
public:
    BucketNode* head;

    HashBucket()
    {
        head = nullptr;
    }
};

#endif
