/*
 * TASK4.H
 *
 *  Created on: 23.09.2019
 *      Author: aml
 */



/**
 *
 * \file TASK4.H
 *
 * \brief Contains namespace TASK4. Namespace TASK4 contains simple demos / examples for thread programming.
 *
 */

#ifndef TASK4_H_
#define TASK4_H_

#include <string>
#include <pthread.h>
#include <iostream>

using namespace std;


/**
 *
 * \namespace TASK4
 *
 * \brief Contains simple demos / examples for thread programming.
 *
 */
namespace TASK4{


void demoTask4();
void demoForkTask4();

void *procA(void* msg);
void *procB(void* msg);


} // end namespace TASK4




#endif /* TASK4_H_ */
