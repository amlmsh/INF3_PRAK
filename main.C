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

#include "SHA256.H"
#include "TASK1.H"
#include "TASK2.H"
#include "TASK3.H"


using namespace std;


int main(){
	srand(time(NULL));

	TASK3::World w(10,10,1,2,3,4);

	w.placeShips();
	w.print();
	w.printBoard();



}





