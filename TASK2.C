/*
 * TASK2.C
 *
 *  Created on: 12.09.2019
 *      Author: aml
 */

#include <iostream>

#include "TASK2.H"

using namespace std;

namespace TASK2{

void demoTASK2(){
	SimFileServer fs(12345,50);
	fs.run(); // endless loop, now use telnet to connect to  the server
}



string SimFileServer::myResponse(string input){
	string msg;
	msg = string("UNKNOWN_COMMAND - Please use:\n");
	msg += string("NEXT\nCHECKSUM\nCONTENT\n");

	if(input.compare(0,4,"NEXT") == 0){
		HtmlFile *fh = new HtmlFile();
		strContent_ = fh->getFile(); // new file
		checkSum_ = sha256(strContent_); // calculate checksum
		msg = string("DONE");
		delete fh;
	}else if(input.compare(0,8,"CHECKSUM") == 0){
		msg = checkSum_;
	}else if(input.compare(0,7,"CONTENT") == 0){
		msg = disturbance(strContent_);
	};
	return msg;
};

string SimFileServer::disturbance(string input){
	const char *charsInput = input.c_str();
	char *charsOutput = new char[input.length()+1];
	char sign;
	for(int i=0; i < input.length(); i++){
		sign = charsInput[i];
		if( (rand() % ((int)(1.0 / noiseRate_)) ) < 1){
			sign++;
		};
		charsOutput[i] = sign;
	}
	charsOutput[input.length()] = '\0';
	string output = string(charsOutput);
	delete [] charsOutput;
	return output;
}


string HtmlFile::generateDataContent(){
	/// \todo this method must create a html table with random float values
	string content("Hallo Welt!");
	return content;
};

string HtmlFile::getBody(){
	string body("");
	body += "<body>";
	body += generateDataContent();
	body += "</body>";
	return body;
};

string HtmlFile::getHead(){
	string head("");
	head += "<head>";
	head += "</head>";
	return head;
};


string HtmlFile::getHtml(){
	string html("");
	html += "<!DOCTYPE html PUBLIC \"-//W3C//DTD XHTML 1.0 Transitional//EN\" \"http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd\">";
	html += "<html xmlns=\"http://www.w3.org/1999/xhtml\">";
	html += getHead();
	html += getBody();
	html += "</html>";
	return html;
};

string HtmlFile::getFile(){
	return fileContent_;
}


void   HtmlFile::newContent(){
	fileContent_ = getHtml();
}

HtmlFile::HtmlFile(){
	newContent();
}


};


