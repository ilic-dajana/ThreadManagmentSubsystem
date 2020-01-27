#ifndef _KERNEVE_H_
#define _KERNEVE_H_
#include "pcb.h"
class PCB;
class KernelEv{
public:
	KernelEv();
	

	void wait();
	void signal();
private:
	PCB* ownEvent;
	volatile int val;
};

#endif