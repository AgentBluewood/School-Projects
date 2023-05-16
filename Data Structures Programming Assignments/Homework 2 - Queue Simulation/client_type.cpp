#include <stdlib.h>
#include "client_type.h"

int clientType::pseudoRandom = 1;

clientType::clientType(int id, int arrvTime, int wTime, int mPacket)
{
	setclientInfo(id, arrvTime, wTime, mPacket);
}

void clientType::setclientInfo(int id, int arrvTime, int wTime, int mPacket)
{
	clientNumber = id;
	arrivalTime = arrvTime;
	waitingTime = wTime;
	maxPackets = mPacket;
	if (mPacket == 0) {
		numOfPackets = 0;
	} else {
		pseudoRandom = (pseudoRandom * 3 + 1) % maxPackets;
		numOfPackets = pseudoRandom + 1;  // number of item is 1 to max
	}
}

int clientType::getWaitingTime() const
{
	return waitingTime;
}

void clientType::setWaitingTime(int time)
{
	waitingTime = time;
}

void clientType::incrementWaitingTime()
{
	waitingTime++;
}

int clientType::getArrivalTime() const
{
	return arrivalTime;
}

int clientType::getNumOfPackets() const
{
	return numOfPackets;
}

int clientType::getclientNumber() const
{
	return clientNumber;
}

