// file: main.cpp
#include <iostream.h>
#include "locks.h"
#include "pcb.h"
#include "timer.h"
#include "idle.h"

int userMain(int argc, char* argv[]);

int main(int argc, char *argv[]) {
	init();

	IdleThread *idleThread = new IdleThread();
	PCB::idle = idleThread->myPCB;

	userMain(argc, argv);

	restore();
	return 0;
}


// #include "sleep.h"|
// int main(int argc, char *argv[]) {

// 	while (1) {

// 		cout << "1. Add" << endl << "2. Update" << endl << "Option: ";
// 		int o;
// 		int time;
// 		cin >> o;

// 		switch(o) {
// 			case 1:
// 				cin >> time;
// 				Sleeping_Thread::addToSleep(NULL, time);
// 				break;
// 			case 2:
// 				Sleeping_Thread::updateSleepList();
// 				break;
// 		}

// 		Sleeping_Thread::printList();

// 	}

// 	return 0;
//}