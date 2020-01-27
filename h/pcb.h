#ifndef _PCB_H_
#define _PCB_H_
#include "thread.h"
#include "locks.h"
#include "sleep.h"


class PCB{

public:

	enum State{ NEW, READY, BLOCKED, TERMINATED};

	// Class for list of pcb (not thread safe)
	class List {
	public:
		List();
		~List();
		
		void put(PCB *pcb);
		void remove(PCB *pcb);
		PCB* get();

	private:
		friend class PCB;
		struct Node{
			PCB *pcb;
			Node *next;
		};
		Node *tail;
		Node *head;
	};

	static List ledgerPCB;
	static PCB* running;
	static PCB *idle;
	static ID getRunningId();
	static Thread* getThreadById(ID id);
	static PCB* getPcbById(ID id);
	static void sleep(Time timeToSleep);
	
	PCB(Thread* thread, StackSize stackSize, Time timeSlice);
	PCB();
	~PCB();

	void start();
	void waitToComplete();
	ID getID();
		

private:
	static int idGenerator;
	static void body();
	friend class KernelEv;
	friend class KernelSem;
	friend class Sleeping_Thread;
	volatile State state;
	StackSize stackSize;
	Thread* myThread;
	Time timeSlice;
	List* blockedPCB;
	unsigned sp, ss, bp;
	unsigned* stack;
	int id;
	friend void interrupt timer(...);

};



#endif