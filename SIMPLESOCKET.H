/*
 * SIMPLESOCKET.H
 *
 *  Created on: 10.09.2019
 *      Author: aml
 */

#ifndef SIMPLESOCKET_H_
#define SIMPLESOCKET_H_

#include <string>
#include <arpa/inet.h> //inet_addr


using namespace std;


class TCPclient{
private:
	int sock;
	string address;
	int port;
	struct sockaddr_in server;

public:
	TCPclient();
	bool conn(string, int);
	bool sendData(string data);
	string receive(int);
};

class TCPserver{
private:
	TCPserver();


	struct sockaddr_in ipOfServer_;
	int    clintListn_ = 0;
	int    clintConnt_ = 0;

public:
	~TCPserver();
	TCPserver(int port, int maxDataSizeRecv);
	void run();

protected:
	const char   *dataSend_;
	char 		 *dataRecv_;
	char   		  maxDataSizeRecv_;
	virtual string        myResponse(string input);

private:
	string response(string incomingMsg);

};




#endif /* SIMPLESOCKET_H_ */
