#include "kerneve.h"
#include "locks.h"
#include "pcb.h"
#include "schedule.h"
#include <dos.h>
KernelEv::KernelEv(): ownEvent(PCB::running), val(0) {}

void KernelEv::wait(){
	if(PCB::running != ownEvent)
		return;
	INTR_LOCK
	if(--val < 0){
		PCB::running->state = PCB::BLOCKED;
		dispatch();
		INTR_UNLOCK
		return;
	}
	INTR_UNLOCK
	
}

void KernelEv::signal(){
	INTR_LOCK
	if(val<0){
		val = 0;
		ownEvent->state = PCB::READY;
		Scheduler::put(ownEvent);
	}else{
		val = 1;
	}
	INTR_UNLOCK
	dispatch();
}
