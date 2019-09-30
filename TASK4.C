/*
 * TASK4.C
 *
 *  Created on: 23.09.2019
 *      Author: aml
 *
 *  Threading examples using POSIX lib (http://en.wikipedia.org/wiki/POSIX_Threads)
 */

#include <string>
#include <iostream>
#include <unistd.h>


#include "TASK4.H"

using namespace std;

namespace TASK4{


void demoTask4(){
	pthread_t t1, t2;
	int i1, i2;
	i1 = pthread_create(&t1, nullptr, procA, (void*) "A");
	i2 = pthread_create(&t1, nullptr, procB, (void*) "B");


	pthread_join(t1,nullptr);
	pthread_join(t2,nullptr);


}

void *procA(void* msg){
	while(1){
		sleep(2);
		cout << "Proc A says: " << (const char *)msg << endl;

	}
	return nullptr;
}

void *procB(void* msg){
	while(1){
		sleep(10);
		cout << "Proc B says: " << (const char *)msg << endl;
	}
	return nullptr;
}


}// end namespace TASK5
