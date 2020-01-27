#include "event.h"
#include "ivtentry.h"
#include "locks.h"
#include "kerneve.h"

Event::Event(IVTNo ivtNo){
	PREEMPT_LOCK
	myImpl = new KernelEv();
	IVTEntry::addEvent(ivtNo, this);
	PREEMPT_UNLOCK
}
Event::~Event(){
	PREEMPT_LOCK
	delete myImpl;
	PREEMPT_UNLOCK
}
void Event::wait(){
	myImpl->wait();	
}
void Event::signal(){
	myImpl->signal();
}
