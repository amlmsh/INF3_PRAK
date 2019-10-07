/*
 * TASK2.H
 *
 *  Created on: 12.09.2019
 *      Author: aml
 */


/**
 *
 * \file TASK2.H
 *
 * \brief Contains namespace TASK2. Namespace TASK2 contains the implementation
 * of demo file servers.
 *
 */

#ifndef TASK2_H_
#define TASK2_H_

#include "SIMPLESOCKET.H"
#include "SHA256.H"


/**
 *
 * \namespace TASK2
 *
 * \brief Contains the implementation
 * of demo file servers.
 *
 */
namespace TASK2{

/**
 *
 * \class SimFileServer
 *
 * \brief Implements a file server providing a simple protocol.
 * The file server has the following 3 commands
 *  (1) \"NEXT\",
 *  (2) \"CHECKSUM\",
 *  (3) \"CONTENT\".
 *
 * If the server receives command \"NEXT\", it creates a new file content.
 * If the server receives command \"CHECKSUM\", its response is the checksum
 * of the current file content.
 * If the server receives command \"CONTENT\", it sends the content of the file as response.
 *
 */
class SimFileServer : public TCPserver{
public:
	/**
	 *
	 * \brief Parameterized constructor
	 *
	 * \param  port int the servers port number
	 * \param maxDataSizeRecv int is the maximal size of a string  the
	 * server can receive.
	 *
	 */
	SimFileServer(int port, int maxDataSizeRecv) :
		TCPserver(port, maxDataSizeRecv){
		strContent_ = "<html><head></head><body>no data</body></html>";
		checkSum_   = sha256(strContent_);
		noiseRate_  = 1.0 / ((float)( (rand() % 10000) + 1));
		/// \todo noiseRate_ shall be parameterizedin this class
	};

protected:

	/**
	 *
	 * \brief Interprets the incoming message and returns the corresponding
	 * response to be sent to the client.
	 *
	 *
	 */
	virtual string myResponse(string input);

	string strContent_;
	string checkSum_;

private:

	/**
	 *
	 * \brief The file content is corrupted by the given noise rate value noiseRate_ .
	 *
	 *
	 */
	virtual string disturbance(string input);


	float noiseRate_;

};

/**
 *
 * \class HtmlFile
 *
 * \brief Class for creating a html file that contains a table with float values.
 *
 */
class HtmlFile{
public:

	/**
	 *
	 * \brief Constructor
	 *
	 */
	HtmlFile();

	/**
	 *
	 * \brief Returns the html file stored in a string.
	 *
	 * \return string representng the html file
	 */
	string getFile();

	/**
	 *
	 * \brief Creates a new html file content.
	 *
	 */
	void   newContent();

protected:
	virtual string generateDataContent();
private:
	virtual string getBody();
	virtual string getHead();
	virtual string getHtml();
	string fileContent_;
};

/**
 * \brief Runs a file server in an endless loop.
 * Via telnet one can connect to the server and send commands.
 *
 */
void demoTASK2();

} // end namespace TASK2


#endif /* TASK2_H_ */
