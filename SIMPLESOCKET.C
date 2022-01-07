/*
 * SIMPLSOCKET.C
 *
 *  Created on: 10.09.2019
 *      Author: aml
 */


/**
C++ client example using sockets
*/
#include <iostream> //cout
#include <cstdio> //printf
#include <cstring> //strlen
#include <string> //string
#include <sys/socket.h> //socket
#include <arpa/inet.h> //inet_addr
#include <netdb.h> //hostent
#include <unistd.h> //contains various constants
#include <sys/types.h> //contains a number of basic derived types that should be used whenever appropriate
#include <netinet/in.h> //contains constants and structures needed for internet domain addresses


#include <cstdio> // standard input and output library
#include <cstdlib> // this includes functions regarding memory allocation
#include <cstring> // contains string functions
#include <cerrno> //It defines macros for reporting and retrieving error conditions through error codes
#include <ctime> //contains various functions for manipulating date and time





#include "SIMPLESOCKET.H"

using namespace std;

TCPclient::TCPclient(){
	sock = -1;
	port = 0;
	address = "";
}

bool TCPclient::conn(string address , int port){
	//create socket if it is not already created
	if(sock == -1){
		//Create socket
		sock = socket(AF_INET , SOCK_STREAM , 0);
		if (sock == -1){
			perror("Could not create socket");
		}

		cout<<"Socket created\n";
	}else { /* OK , nothing */ }

	//setup address structure
	if(inet_addr(address.c_str()) == -1){
		struct hostent *he;
		struct in_addr **addr_list;

		//resolve the hostname, its not an ip address
		if ( (he = gethostbyname( address.c_str() ) ) == NULL){
			//gethostbyname failed
			herror("gethostbyname");
			cout<<"Failed to resolve hostname\n";

			return false;
		}

		//Cast the h_addr_list to in_addr , since h_addr_list also has the ip address in long format only
		addr_list = (struct in_addr **) he->h_addr_list;

		for(int i = 0; addr_list[i] != NULL; i++){
			//strcpy(ip , inet_ntoa(*addr_list[i]) );
			server.sin_addr = *addr_list[i];

			cout<<address<<" resolved to "<<inet_ntoa(*addr_list[i])<<endl;

			break;
		}
	}else{//plain ip address
		server.sin_addr.s_addr = inet_addr( address.c_str() );
	}

	server.sin_family = AF_INET;
	server.sin_port = htons( port );

	//Connect to remote server
	if (connect(sock , (struct sockaddr *)&server , sizeof(server)) < 0){
		perror("connect failed. Error");
		return 1;
	}

	cout<<"Connected\n";
	return true;
}

/**
Send data to the connected host
*/
bool TCPclient::sendData(string data){
	//Send some data
	if( send(sock , data.c_str() , strlen( data.c_str() ) , 0) < 0){
		perror("Send failed : ");
		return false;
	}

	return true;
}

/**
Receive data from the connected host
*/
string TCPclient::receive(int size=512){
	char buffer[size];
	string reply;

	//Receive a reply from the server
	if( recv(sock , buffer , sizeof(buffer) , 0) < 0){
		puts("recv failed");
	}

	reply = buffer;
	return reply;
}




TCPserver::TCPserver(int port, int maxDataSizeRecv){
	maxDataSizeRecv_ = maxDataSizeRecv;
	dataRecv_ = new char[maxDataSizeRecv_];

	clintListn_ = socket(AF_INET, SOCK_STREAM, 0); // creating socket

	memset(&ipOfServer_, '0', sizeof(ipOfServer_));

	ipOfServer_.sin_family = AF_INET;
	ipOfServer_.sin_addr.s_addr = htonl(INADDR_ANY);
	ipOfServer_.sin_port = htons(port); 		// this is the port number of running server

	bind(clintListn_, (struct sockaddr*)&ipOfServer_ , sizeof(ipOfServer_));


}


void TCPserver::run(){

	string input, output;

	listen(clintListn_, 20);
	clintConnt_ = accept(clintListn_, (struct sockaddr*)NULL, NULL);

	while(1)
	{
		for(int i=0; i < maxDataSizeRecv_; i++){
			dataRecv_[i] = '\0';
 		}

		read(clintConnt_,dataRecv_, (size_t)maxDataSizeRecv_);
		output = response(string(dataRecv_));
		dataSend_ = output.c_str();
		write(clintConnt_, dataSend_, strlen(dataSend_)+1);
		if(output.compare(0,6,"BYEBYE") == 0){
			cout << "asked to close server\n";
			break;
		}
     }
    close(clintConnt_);
    sleep(1);

}

TCPserver::~TCPserver(){
	delete [] dataRecv_;
}

string TCPserver::response(string incomingMsg){
	string msg;
	if(incomingMsg.compare(0,6,"BYEBYE") == 0){
		cout << "asked to close server\n";
		msg = string("BYEBYE"); // this return value
		                        // will close server connections
	}else{
		msg = myResponse(incomingMsg);
	}

	cout << "received :" << incomingMsg << endl;
	cout << "send back:" << msg << endl;

	return msg;
}


string TCPserver::myResponse(string input){
	return string("NO DATA YET YET YET");
}











