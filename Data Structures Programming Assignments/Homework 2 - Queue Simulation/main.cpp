#include <iostream>
#include <cmath>
#include "client_type.h"
#include "server_list_type.h"
#include "waiting_client_queue_type.h"


using namespace std;

void setSimulationParameters(int& sTime, int& numOfServers, int& maxPacket, int& tBetweenCArrival)
{
	cout << "Enter the simulation time: ";
	cin >> sTime;
	cout << endl;
	cout << "Enter the number of servers: ";
	cin >> numOfServers;
	cout << endl;
	cout << "Enter the maximum number of packets: ";
	cin >> maxPacket;
	cout << endl;
	cout << "Enter the time between clients arrival: ";
	cin >> tBetweenCArrival;
	cout << endl;
}


int main()
{
	int clock; //simulation global clock
	int time, numOfServers, maxPacket, betweenArrival; //simulation parameters
	int totalWaitTime = 0;
	int clientsArrived = 0;
	int clientsServed = 0;

	// === Prepare the parameters ===

	setSimulationParameters(time, numOfServers, maxPacket, betweenArrival);

	cout << endl;
	cout << "Simulation time: " << time << endl;
	cout << "Number of servers:  " << numOfServers << endl;
	cout << "Maximum number of packets: " << maxPacket << endl;
	cout << "Average time between clients arrival: " << betweenArrival << endl << endl;

	// === Prep the servers and the queue ===

	serverListType serverList(numOfServers);
	waitingClientQueueType clientQueue;
	double lambda = (double) 1 / betweenArrival;
	int p = 42;
	// === The big loop to simulate the world

	for (clock = 1; clock <= time; clock++)
	{
		// Update servers' current state
		serverList.updateServers(cout);

		// Update clients' current state
		if (!clientQueue.isEmptyQueue())
			clientQueue.updateWaitingQueue();

		p = (p * 7 + 3) % 100;
		
		if ( p/100.0 > exp(-lambda))
		{
			// If a new client arrives, put him in the queue
			clientType client(clientsArrived, clock, 0, maxPacket);
			cout << "Client number " << ++clientsArrived << " arrived at time step " << clock <<
				" with " << client.getNumOfPackets() << " packets." << endl;
			clientQueue.enQueue(client);
		}

		if (serverList.getFreeServerID() != -1 && !clientQueue.isEmptyQueue())
		{
			// If there is a server available, take a client from the queue to the server
			clientType client = clientQueue.front();
			clientQueue.deQueue();

			serverList.setServerBusy(serverList.getFreeServerID(), client);
			totalWaitTime = totalWaitTime + client.getWaitingTime();
			clientsServed++;
		}

	}


	cout << endl;
	cout << "Simulation run for " << time << " time units" << endl;
	cout << "Clients arrived: " << clientsArrived << endl;
	cout << "Total number of clients who have been served: " << clientsServed << endl;
	cout << "Clients left in servers: " << serverList.getNumberOfBusyServers() << endl;
	cout << "Clients left in queue: " << clientsArrived - clientsServed << endl;
	cout << "Total waiting time: " << totalWaitTime << endl;
	cout << "Average waiting time: " << (double)totalWaitTime / clientsServed;

	return 0;
}
