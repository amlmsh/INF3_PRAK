/*
 * TASK4.H
 *
 *  Created on: 23.09.2019
 *      Author: aml
 */

#ifndef TASK4_H_
#define TASK4_H_

#include <string>
#include <pthread.h>
#include <iostream>

using namespace std;



namespace TASK4{


void demoTask4();

void *procA(void* msg);
void *procB(void* msg);


} // end namespace TASK4




#endif /* TASK4_H_ */
