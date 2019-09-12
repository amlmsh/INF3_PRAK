/*
 * TASK2.H
 *
 *  Created on: 12.09.2019
 *      Author: aml
 */

#ifndef TASK2_H_
#define TASK2_H_

#include "SIMPLESOCKET.H"
#include "SHA256.H"

namespace TASK2{

class SimFileServer : public TCPserver{
public:
	SimFileServer(int port, int maxDataSizeRecv) :
		TCPserver(port, maxDataSizeRecv){
		strContent_ = "<html><head></head><body>no data</body></html>";
		checkSum_   = sha256(strContent_);
		noiseRate_  = 1.0 / ((float)( (rand() % 10000) + 1));
	};

protected:
	virtual string myResponse(string input);
	string strContent_;
	string checkSum_;

private:
	virtual string disturbance(string input);
	float noiseRate_;

};


class HtmlFile{
public:
	HtmlFile();
	string getFile();
	void   newContent();
protected:
	virtual string generateDataContent();
private:
	virtual string getBody();
	virtual string getHead();
	virtual string getHtml();
	string fileContent_;
};

} // end namespace TASK2


#endif /* TASK2_H_ */
