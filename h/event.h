#ifndef _EVENT_H_
#define _EVENT_H_
#include "ivtentry.h"

typedef unsigned char IVTNo;
class KernelEv;

//PREPAREENTRY macro for def data
//numEntry - number of entry in def func
//callOldFlag - flag for calling old interrupt routine (1 yes, 0 no)
#define PREPAREENTRY(numEntry, callOldFlag)\
void interrupt inter##numEntry(...){\
	if(callOldFlag==1)\
		IVTEntry::callOldInterruptRoutine(numEntry);\
	IVTEntry::signal(numEntry);\
}\
IVTEntry newEntry##numEntry(numEntry, inter##numEntry);

class Event {
public:
	Event(IVTNo ivtNo);
	~Event();

	void wait();
protected:
	friend class IVTEntry;
	friend class KernelEvent;
	void signal();
private:
	KernelEv *myImpl;

};

#endif