#ifndef _SLEEP_H_
#define _SLEEP_H_
#include "pcb.h"
#include "timer.h"
#include "thread.h"
class Sleeping_Thread {
public:
	static void addToSleep(PCB* pcb, Time timeToWait);
	static void updateSleepList();
	static void removeFromSleepList(PCB *target);
	static void printList();
private:
	struct SleepNode{
		PCB *pcb;
		Time leftToSleep;
		SleepNode *next;
	};

friend void interrupt timer(...);
static SleepNode *head;
static SleepNode *tail;
};
#endif
