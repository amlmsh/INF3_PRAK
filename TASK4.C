/*
 * TASK4.C
 *
 *  Created on: 23.09.2019
 *      Author: aml
 */

#include <string>
#include <thread>
#include <iostream>

#include "TASK4.H"

using namespace std;

namespace TASK4{

void demoTask4(){
	thread t1(procA, "hello");
	thread t2(procB, "Hallo");


	t1.join();
	t2.join();


}

void procA(string msg){
	while(1){
		cout << "Proc A says: " << msg << endl;
	}
}

void procB(string msg){
	while(1){
		cout << "Proc B says: " << msg << endl;
	}
}


}
