#include "server_type.h"

serverType::serverType()
{
	status = "free";
	currentNumOfPackets = 0;
}

bool serverType::isFree() const
{
	return (status == "free");
}

void serverType::setBusy()
{
	status = "busy";
}

void serverType::setFree()
{
	status = "free";
}

void serverType::setCurrentNumOfPackets(int t)
{
	currentNumOfPackets = t;
}

void serverType::setCurrentNumOfPackets()
{
	currentNumOfPackets = currentClient.getNumOfPackets();
}

int serverType::getRemainingTransactionTime() const
{
	return currentNumOfPackets;
}

void serverType::decreaseTransactionTime()
{
	currentNumOfPackets--;
}

void serverType::setCurrentClient(clientType cClient)
{
	currentClient = cClient;
}

int serverType::getCurrentClientNumber() const
{
	return currentClient.getclientNumber();
}

int serverType::getCurrentClientArrivalTime() const
{
	return currentClient.getArrivalTime();
}

int serverType::getCurrentClientWaitingTime() const
{
	return currentClient.getWaitingTime();
}

int serverType::getCurrentClientNumOfPackets() const
{
	return currentClient.getNumOfPackets();
}
