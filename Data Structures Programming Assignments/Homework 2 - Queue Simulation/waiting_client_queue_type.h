#ifndef WAITING_CLIENT_QUEUE_TYPE_H
#define WAITING_CLIENT_QUEUE_TYPE_H

#include "client_type.h"
#include "queue_type.h"


class waitingClientQueueType : public queueType<clientType>
{
public:
	waitingClientQueueType(int size = 100);
	void updateWaitingQueue();
};

#endif // !WAITING_CLIENT_QUEUE_TYPE_H
