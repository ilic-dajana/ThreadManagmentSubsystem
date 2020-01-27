#include "locks.h"
#include<dos.h>
#include "pcb.h"
#include "thread.h"
#include "scheduler.h"
#include "sleep.h"
int PCB::idGenerator = 0;
PCB* PCB::running = 0;
PCB::List PCB::ledgerPCB;
PCB* PCB::idle = 0;

PCB::PCB(): sp(0), bp(0), ss(0), stack(0), 
timeSlice(defaultTimeSlice), id(PCB :: idGenerator++), stackSize(defaultStackSize), state(PCB :: READY){
	blockedPCB = new PCB::List();
}

PCB::PCB(Thread* thread, StackSize stackSize, Time timeSlice){

	this->myThread = thread;
	this->stackSize = stackSize;
	this->timeSlice = timeSlice;
	this->id = PCB::idGenerator++;
	this->stack = new unsigned[stackSize/2];

	stack[stackSize/2 - 1] = 0x200; //Set the flag I for interrupts
	stack[stackSize/2 - 2] = FP_SEG(PCB :: body); // put the body function of the pcb(thread)
	stack[stackSize/2 - 3] = FP_OFF(PCB :: body);

	this->sp = FP_OFF(stack + (stackSize/2 - 12));
	this->ss = FP_SEG(stack + (stackSize/2 - 12));
	this->bp = 0;
	this->state = PCB::NEW;
	blockedPCB = new PCB::List();
	PCB::ledgerPCB.put(this);
}

PCB::~PCB(){
	PCB :: ledgerPCB.remove(this);
	delete blockedPCB;
	if (stack)
		delete []stack;
}

void PCB::body(){
	PCB::running->myThread->run();

	PREEMPT_LOCK
	PCB *temp = 0;
	while(temp = PCB::running->blockedPCB->get()){
		temp->state = PCB::READY;
		Scheduler::put(temp);
	}
	PCB::running->state = PCB::TERMINATED;
	PREEMPT_UNLOCK

	dispatch();
}

ID PCB::getID(){
	return this->id;
}

ID PCB::getRunningId(){
	return running->getID();
}

void PCB::start(){
	PREEMPT_LOCK
	if(state == PCB::NEW){
		state = PCB::READY;
		Scheduler::put(this);
	}	
	PREEMPT_UNLOCK
}

PCB* PCB::getPcbById(ID id){
	List::Node* temp = ledgerPCB.head;
	
	while(temp && temp->pcb->id != id)
		temp = temp->next;
	
	if(temp == 0)
		return 0;
	
	return temp->pcb;
}

Thread* PCB::getThreadById(ID id){
	List::Node* temp = ledgerPCB.head;
	
	while(temp && temp->pcb->id != id)
		temp = temp->next;
	
	if(temp == 0)
		return 0;
	
	return temp->pcb->myThread;
}

void dispatch(){
	if (preemptionDisabled)
		return;
	
	INTR_LOCK
	switchContextOnRequest = 1;
	explicitCallForTimer = 1;
	timer();
	INTR_UNLOCK
}

void PCB::waitToComplete(){
	if((PCB::state==PCB::TERMINATED)||(this==PCB::idle))
		return;

	PREEMPT_LOCK
	PCB::running->state = PCB::BLOCKED;
	blockedPCB->put(PCB::running);
	PREEMPT_UNLOCK

	dispatch();
}

void PCB::sleep(Time timeToSleep){
	if(timeToSleep == 0)
		return;
	INTR_LOCK
	PCB::running->state = PCB::BLOCKED;
	Sleeping_Thread::addToSleep(PCB::running, timeToSleep);
	INTR_UNLOCK
	dispatch();
}

// class List methods
PCB::List::List(): tail(0), head(0){

} 

PCB::List::~List(){
	Node* temp = head;
	while(temp){
		head = temp->next;
		delete temp;
		temp = head;
	}
	head = 0;
	tail = 0;
}

void PCB::List::put(PCB *pcb){
	Node* addNode = new Node;
	addNode->pcb = pcb;
	addNode->next = 0;

	if(head == 0){
		head = tail = addNode;
	}
	else{
		tail->next = addNode;
		tail = addNode;
	}
} 

void PCB::List::remove(PCB *pcb){
	Node* temp = head;
	Node* prev = 0;
	while(temp && temp->pcb != pcb){
		prev = temp;
		temp = temp->next;
	}

	if(temp == 0)
		return;
	
	if(temp == head){
		head = head->next;
	}
	if(temp == tail){
		tail = prev;
		tail->next = 0;
	}else {
		prev->next = temp->next;
	}
	
	delete temp;
}

PCB* PCB::List::get(){
	Node* temp = head;
	PCB* retv;

	if(temp == 0)
		return 0;
	if(temp == tail)
		tail = head = 0;
	else
		head = head->next;

	retv = temp->pcb;
	delete temp;
	return retv;
}