#include "idle.h"


IdleThread::IdleThread(): Thread(512,1) { }


#include <iostream.h>
#include "locks.h"

void IdleThread::run(){
	 while(1){
		// PREEMPT_LOCK
		// cout << "idle" << endl;
		// PREEMPT_UNLOCK
	}
}