/*
 * TASK1.H
 *
 *  Created on: 10.09.2019
 *      Author: aml
 */

#ifndef TASK1_H_
#define TASK1_H_

#include <string>

using namespace std;

namespace TASK1{

const string SYMBOLS = "ABCDEFGHIJKLMNOPQRTSTUVWXYZabcdefghijklmopqrstuvwxyz0123456789";

class IBlackBox{
public:
	virtual string input(string strPwd) = 0;
	virtual string getSymbols() = 0;
};


class BlackBoxUnsafe : public IBlackBox{
public:
				   BlackBoxUnsafe(int pwdLength, int symbSetSize);
	virtual string input(string strPwd);
			string getSymbols();

			string pwd_;

protected:
	string randomPwd(int pwdLength);
	char * charSymbArray_;
	int    lengthSymbArray_;
};


class BlackBoxSafe : public BlackBoxUnsafe{
public:
	BlackBoxSafe(int l=8);
	virtual string input(string strPwd);
};


}


#endif /* TASK1_H_ */
