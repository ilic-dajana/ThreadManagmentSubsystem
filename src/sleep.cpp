#include "pcb.h"
#include "sleep.h"
#include "thread.h"
#include "schedule.h"

Sleeping_Thread::SleepNode* Sleeping_Thread::head = 0;
Sleeping_Thread::SleepNode* Sleeping_Thread::tail = 0;

void Sleeping_Thread::addToSleep(PCB* pcb, Time timeToWait){	
	SleepNode* newNode = new SleepNode;
	SleepNode* cur = head;
	SleepNode* prev = 0;
	newNode->pcb = pcb;
	newNode->next = 0;

	if (head==0){
		newNode->leftToSleep = timeToWait;		
		head = tail = newNode;
	}
	else{
	
		while(cur && cur->leftToSleep <= timeToWait){
			timeToWait -= cur->leftToSleep;
			prev = cur;
			cur = cur->next;
		}
		newNode->leftToSleep = timeToWait;
		if(prev)
			prev->next = newNode;
		if(cur){
			newNode->next = cur;
			cur->leftToSleep -= timeToWait; 
			if(cur == head)
				head = newNode;
		}else{
			tail = newNode;
		}


	}

}	

#include <iostream.h>
void Sleeping_Thread::printList()
{
	SleepNode *p = head;
	while (p!=0) {
		cout << p->leftToSleep << " -> ";
		p = p->next;
	}
	cout << endl;
}

void Sleeping_Thread::updateSleepList(){
	if(head == 0)
		return;

	SleepNode* temp;
	--(head->leftToSleep);
	while(head && head->leftToSleep == 0)
	{
		temp = head;
		head = head->next;
		temp->pcb->state = PCB::READY;
		Scheduler::put(temp->pcb);
	}
}

void Sleeping_Thread::removeFromSleepList(PCB *target){
	SleepNode* cur = head;
	SleepNode* prev = 0;

	while(cur && cur->pcb != target){
		prev = cur;
		cur = cur->next;
	}
	if(!cur)
		return;
	if(cur->next)
		cur->next->leftToSleep += cur->leftToSleep;
	if(prev)
		prev->next = cur->next;
	else
		head = cur->next;
	delete cur;
}
