#ifndef SERVER_TYPE_H
#define SERVER_TYPE_H

#include <string>
#include "client_type.h"

class serverType
{
public:
	serverType();
	bool isFree() const;
	void setBusy();
	void setFree();
	void setCurrentNumOfPackets(int t);
	void setCurrentNumOfPackets();
	int getRemainingTransactionTime() const;
	void decreaseTransactionTime();
	void setCurrentClient(clientType cClient);
	int getCurrentClientNumber() const;
	int getCurrentClientArrivalTime() const;
	int getCurrentClientWaitingTime() const;
	int getCurrentClientNumOfPackets() const;

private:
	clientType currentClient;
	std::string status;
	int currentNumOfPackets;
};

#endif // !SERVER_TYPE_H

