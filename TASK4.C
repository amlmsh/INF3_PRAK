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

void demoForkTask4(){
    printf("PROGRAMMSTART\n");

    int i;
    int counter = 0;
    pid_t pid = fork();

    if (pid == 0){
        for (i=0;i<15;i++){
            printf("            PID: %d; ", getpid());
            printf("Kindprozess: counter=%d\n", counter++);
            sleep(2);
        }
    }
    else if (pid > 0){
        for (i=0;i<10;i++){
            printf("PID: %d; ", getpid());
            printf("Elternprozess: counter=%d\n", counter++);
            sleep(3);
        }
    }
    else{
        printf("fork() fehlgeschlagen!\n");
        exit(1);
    }

    printf("PROGRAMMENDE\n");
    exit(0);
}


void demoTask4(){
	pthread_t t1, t2;
	int i1, i2;
	i1 = pthread_create(&t1, nullptr, procA, (void*) "A");
	i2 = pthread_create(&t2, nullptr, procB, (void*) "B");


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
