#include "waiting_client_queue_type.h"


waitingClientQueueType::waitingClientQueueType(int size)
	:queueType<clientType>(size)
{

}

void waitingClientQueueType::updateWaitingQueue()
{
	clientType cust;
	cust.setWaitingTime(-1);
	int wTime = 0;
	enQueue(cust);
	while (wTime != -1)
	{
		cust = front();
		deQueue();
		wTime = cust.getWaitingTime();
		if (wTime == -1)
			break;
		cust.incrementWaitingTime();
		enQueue(cust);
	}
}


