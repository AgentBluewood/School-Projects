#ifndef CLIENT_TYPE_H
#define CLIENT_TYPE_H

class clientType
{
public:
	clientType(int id = 0, int arrvTime = 0,
		int wTime = 0, int mItem = 0);
	void setclientInfo(int id = 0, int inTime = 0,
		int wTime = 0, int mItem = 0);
	int getWaitingTime() const;
	void setWaitingTime(int time);
	void incrementWaitingTime();
	int getArrivalTime() const;
	int getNumOfPackets() const;
	int getclientNumber() const;

private:
	int clientNumber;
	int arrivalTime;
	int waitingTime;
	int maxPackets;
	int numOfPackets;
	static int pseudoRandom;
};

#endif // !CLIENT_TYPE_H


