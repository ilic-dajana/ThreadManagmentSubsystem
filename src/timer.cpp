#include "timer.h"
#include "locks.h"
#include "schedule.h"
#include <dos.h>
#include "pcb.h"
#include "sleep.h"

unsigned long timeCounter = defaultTimeSlice;
volatile unsigned preemptionDisabled = 0;
volatile char switchContextOnRequest = 0;
volatile char explicitCallForTimer = 0;
static volatile unsigned infinityFlag = 0;
static volatile unsigned tsp;
static volatile unsigned tss;
static volatile unsigned tbp;


void interrupt timer(...){

	if(!explicitCallForTimer){
		asm int 60h;
		tick();
		--timeCounter;
		Sleeping_Thread::updateSleepList();
	}
	explicitCallForTimer = 0;

	if((!infinityFlag && timeCounter ==0) || switchContextOnRequest){

		if(!preemptionDisabled){
			switchContextOnRequest = 0;


			asm{
				mov tsp, sp
				mov tss, ss
				mov tbp, bp
				}
			
			PCB::running->sp = tsp;
			PCB::running->ss = tss;
			PCB::running->bp = tbp;
	
	if((PCB::running != PCB::idle) && (PCB::running->state == PCB::READY))		
		Scheduler::put(PCB::running);	
		
	if((PCB::running=Scheduler::get()) == 0)	
		PCB::running = PCB::idle;

			tsp = PCB::running->sp;
			tss = PCB::running->ss;
			tbp = PCB::running->bp;

			timeCounter = PCB::running->timeSlice;
			infinityFlag = timeCounter > 0 ? 0 : 1;
			
			asm{
				mov sp, tsp
				mov ss, tss
				mov bp, tbp
				}	

		}
		else {
			switchContextOnRequest = 1;
		}
	}
}

static void interrupt (*oldInte)(...);
void init(){
	INTR_LOCK
	PCB :: running = new PCB();
 	oldInte = getvect(0x8);
	setvect(0x60, oldInte);
	setvect(0x8, timer);
	INTR_UNLOCK
}

void restore(){
	INTR_LOCK
	delete PCB :: running;
	setvect(0x8,oldInte);
	INTR_UNLOCK
}