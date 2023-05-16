#ifndef SERVER_LIST_TYPE_H
#define SERVER_LIST_TYPE_H

#include <iostream>
#include "client_type.h"
#include "server_type.h"


class serverListType
{
public:
	serverListType(int num = 1);
	~serverListType();
	int getFreeServerID() const;
	int getNumberOfBusyServers() const;
	void setServerBusy(int serverID, clientType cClient, int tTime);
	void setServerBusy(int serverID, clientType cCLient);
	void updateServers(std::ostream& outFile);

private:
	int numOfServers;
	serverType* servers;
};

#endif // !SERVER_LIST_TYPE_H

