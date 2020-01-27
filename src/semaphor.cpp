#include "kernsem.h"
#include "semaphor.h"

Semaphore::Semaphore(int init){
	PREEMPT_LOCK
	myImpl = new KernelSem(init);
	PREEMPT_UNLOCK
}


Semaphore::~Semaphore(){
	PREEMPT_LOCK
	delete myImpl;
	PREEMPT_UNLOCK
}

int Semaphore::wait(int toBlock){
	return myImpl->wait(toBlock);
}

void Semaphore::signal(){
	myImpl->signal();
}

int Semaphore::val()const {
	return myImpl->val();
}

