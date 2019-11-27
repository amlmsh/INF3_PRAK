/*
 * mainTest.c
 *
 *  Created on: 27.11.2019
 *      Author: aml
 */

//============================================================================
// Name        : INF3_Prak.cpp
// Author      :
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C, Ansi-style
//============================================================================

#include <string>
#include <iostream>

#include <cstdio>      /* printf, NULL */
#include <cstdlib>     /* srand, rand */
#include <ctime>       /* time */

#include <unistd.h>

#include "SHA256.H"
#include "TASK1.H"
#include "TASK2.H"
#include "TASK3.H"
#include "TASK4.H"
#include "TASK5.H"
#include "TASK6.H"

using namespace std;

class InputTest_A : public TASK6::TestCase{
public:
	InputTest_A(string s) : TASK6::TestCase(s){};
	bool testRun(){
		TASK1::BlackBoxUnsafe  bbs(4,4);
		cout << bbs.input("XXX") << endl;
		if( (bbs.input("XXX")).compare("ACCESS DENIED") == 0 ){
			return true;
		}
		return false;
	}
};


class InputTest_B : public TASK6::TestCase{
public:
	InputTest_B(string s) : TASK6::TestCase(s){};
	bool testRun(){
		TASK1::BlackBoxUnsafe  bbs(4,4);
		if( (bbs.input(bbs.pwd_)).compare("ACCESS DENIED") == 0 ){
			return true;
		}
		return false;
	}
};


int main(){
	srand(time(nullptr));

	TASK6::UnitTest     ut("BlackBoxUnsafe");
	TASK6::TestSuite    tSuite("input methode");
	InputTest_A         tA("check incorrect pwd");
	InputTest_B         tB("check correct pwd");

	ut.addTestItem(&tSuite);
	tSuite.addTestItem(&tA);
	tSuite.addTestItem(&tB);


	ut.testExecution();
	ut.writeResultsToFile("out.xml");

    return 0;
}

