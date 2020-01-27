#ifndef _KERNSEM_H_
#define _KERNSEM_H_
#include "pcb.h"
class PCB;

class KernelSem{
public:
	class List {
	public:
		List();
		~List();

		void put(PCB* pcb);
		PCB* get();
		void remove(PCB* targetPCB);
	private:	
		struct Node{
			char isblocked;
			PCB *pcb;
			Node *next;

		};
		friend class KernelSem;
		Node *head;
		Node *tail;
	};

	KernelSem(int init=1);
	~KernelSem();

	int wait(int toBlock);
	void signal();
	int val()const;
private:
	volatile int value;
	List *blocked;
	void block();
	void deblock();

};
#endif