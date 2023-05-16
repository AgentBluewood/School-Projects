#ifndef QUEUE_TYPE_H
#define QUEUE_TYPE_H

#include <iostream>
#include <cassert>
#include "queueADT.h"

using namespace std;

template <class Type>
class queueType : public queueADT<Type>
{
public:
	queueType(int queueSize = 100) {
    // implement constructor
        if (queueSize < 0) {
            queueSize = 100;
        }
        maxQueueSize = queueSize;
        list = new Type[maxQueueSize];
        
        queueRear = 0;
        queueFront = 0;
        count = 0;
	}

	~queueType() {
	// implement destructor
        delete [] list;
	}

	bool isEmptyQueue() const {
		return (count == 0);
	}

	bool isFullQueue() const {
		return (count == maxQueueSize);
	}
	
   int getSize() const {
      return count;
   }

   int getMaxCapacity() const {
      return maxQueueSize;
   }

	void initializeQueue() {
    // implement function
    
	}

	Type front() const {
		assert(!isEmptyQueue());
		return list[queueFront];
	}

	Type back() const {
		assert(!isEmptyQueue());
        if ((queueRear - 1) < 0) {
            return list[maxQueueSize - 1];
        } else {
            return list[queueRear - 1];
        }
	}

	void enQueue(const Type& queueElement) {
   // implement function
        if (isFullQueue() == true) {
            cout << "Can not add to a full queue" << endl;
        } else {
            list[queueRear] = queueElement;
            queueRear = (queueRear + 1) % maxQueueSize;
            count++;
            cout << "New client added. Queue now has " << count << " clients." << endl;
        }
	}

	void deQueue() {
	// implement function
        if (isEmptyQueue() == true) {
            cout << "Cannot remove from an empty queue" << endl;
        } else {
            queueFront = (queueFront + 1) % maxQueueSize;
            count--;
            cout << "Client removed from queue. Queue now has " << count << " clients." << endl;
        }
	}


private:
	int maxQueueSize; //variable to store the maximum queue size
	int count; //variable to store the number of
	int queueFront; //variable to point to the first
	int queueRear; //variable to point to the last
	Type* list; //pointer to the array that holds
};

#endif // !QUEUE_TYPE_H
