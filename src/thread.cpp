#include "thread.h"
#include "locks.h"
#include <dos.h>
#include "pcb.h"


void Thread::start(){
	myPCB->start();
}

void Thread::waitToComplete(){
	myPCB->waitToComplete();
}

Thread::~Thread(){
    waitToComplete();
    PREEMPT_LOCK
    delete myPCB;
    PREEMPT_UNLOCK
}

/*ID Thread::getId(){
	return myPCB->getID();
}

ID Thread::getRunningId(){
	return PCB :: getRunningId();
}

Thread* Thread::getThreadById(ID id){
return PCB :: getThreadById(id);
}*/

Thread::Thread(StackSize stackSize, Time timeSlice ){
	PREEMPT_LOCK
	if(maxStackSize < stackSize)
		stackSize = maxStackSize;
	myPCB = new PCB(this, stackSize, timeSlice);
	PREEMPT_UNLOCK
}

void Thread::sleep(Time timeToSleep){
	PCB::sleep(timeToSleep);
}