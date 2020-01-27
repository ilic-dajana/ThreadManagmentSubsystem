#include "kernsem.h"
#include "locks.h"
#include "schedule.h"
#include "pcb.h"
#include <dos.h>

KernelSem::KernelSem(int init){
	value = init;
	blocked = new KernelSem::List();
}

KernelSem::~KernelSem(){
	delete blocked;
}

int KernelSem::val()const{
	return value;
}

int KernelSem::wait(int toBlock){
	INTR_LOCK
	if(toBlock!= 0){
		--value;
		if(value < 0){
			block();
			INTR_UNLOCK
			return 1;
		}
		else {
			INTR_UNLOCK
			return 0;
		}

	} else if(value <= 0){
		INTR_UNLOCK
			return -1;
		}
		else{ // proveri da li se u ovom slucaju umanjuje val
		INTR_UNLOCK
			return 0;
		}

}

void KernelSem::signal(){
	INTR_LOCK
	if(value++ < 0)
		deblock();
	INTR_UNLOCK

}

void KernelSem::block(){
	PCB::running->state = PCB::BLOCKED;
	blocked->put(PCB::running);
	dispatch();
}

void KernelSem::deblock(){
	PCB *pcb = blocked->get();
	pcb->state = PCB::READY;
	Scheduler::put(pcb);


}





//class List
KernelSem::List::List() {
	head = 0;
	tail = 0;
}

KernelSem::List::~List(){
	Node* temp = head;
	while(temp){
		head = temp->next;
		delete temp;
		temp = head;
	}
	head = 0;
	tail = 0;
}

void KernelSem::List::put(PCB *pcb){
	Node *addNode = new Node();
	addNode->pcb = pcb;
	addNode->next = 0;

	if(head == 0)
		head=tail=addNode;
	else {
		tail->next = addNode;
		tail = addNode;
	}
}

void KernelSem::List::remove(PCB *pcb){
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

PCB* KernelSem::List::get(){
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