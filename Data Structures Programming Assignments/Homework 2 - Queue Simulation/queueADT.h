#ifndef QUEUE_ADT_H
#define QUEUE_ADT_H

template <class Type>
class queueADT
{
public:
	virtual bool isEmptyQueue() const = 0;
	virtual bool isFullQueue() const = 0;
   virtual int getSize() const = 0;
   virtual int getMaxCapacity() const = 0;
	virtual void initializeQueue() = 0;
	virtual Type front() const = 0;
	virtual Type back() const = 0;
	virtual void enQueue(const Type& queueElement) = 0;
	virtual void deQueue() = 0;
};

#endif // !QUEUE_ADT_H
