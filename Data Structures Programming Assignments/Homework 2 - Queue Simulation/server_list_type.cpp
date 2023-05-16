#include "server_list_type.h"

using namespace std;

serverListType::serverListType(int num)
{
	numOfServers = num;
	servers = new serverType[num];
}

serverListType::~serverListType()
{
	delete[] servers;
}

int serverListType::getFreeServerID() const
{
	int serverID = -1;
	for (int i = 0; i < numOfServers; i++)
		if (servers[i].isFree())
		{
			serverID = i;
			break;
		}
	return serverID;
}

int serverListType::getNumberOfBusyServers() const
{
	int busyServers = 0;
	for (int i = 0; i < numOfServers; i++)
		if (!servers[i].isFree())
			busyServers++;
	return busyServers;
}

void serverListType::setServerBusy(int serverID, clientType cClient, int tTime)
{
	servers[serverID].setBusy();
	servers[serverID].setCurrentNumOfPackets(tTime);
	servers[serverID].setCurrentClient(cClient);
}

void serverListType::setServerBusy(int serverID, clientType cClient)
{
	int item = cClient.getNumOfPackets();
	servers[serverID].setBusy();
	servers[serverID].setCurrentNumOfPackets(item);
	servers[serverID].setCurrentClient(cClient);
}

void serverListType::updateServers(std::ostream& outFile)
{
	for (int i = 0; i < numOfServers; i++)
		if (!servers[i].isFree())
		{
			servers[i].decreaseTransactionTime();
			if (servers[i].getRemainingTransactionTime() == 0)
			{
				outFile << "From server number " << (i + 1)
					<< " client number "
					<< servers[i].getCurrentClientNumber()
					<< "\n departed at clock unit "
					<< servers[i].getCurrentClientArrivalTime()
					+ servers[i].getCurrentClientWaitingTime()
					+ servers[i].getCurrentClientNumOfPackets()
					<< endl;
				servers[i].setFree();
			}
		}
}
