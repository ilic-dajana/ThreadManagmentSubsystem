#ifndef _thread_h_
#define _thread_h_

typedef unsigned long StackSize;
const StackSize maxStackSize = 1L<<16;
const StackSize defaultStackSize = 4096;
typedef unsigned int Time; // time, x 55ms
const Time defaultTimeSlice = 2; //default = 2*55ms
typedef int ID;

class PCB; //Kernel's implementation of user's thread

class Thread { 
public:

	void start();
	void waitToComplete();
	virtual ~Thread();

	static void sleep(Time timeToSleep);
	
//	ID getId();
//	static ID getRunningId();
//	static Thread* getThreadById(ID id);

	
protected:
	Thread(StackSize stackSize = defaultStackSize, Time timeSlice = defaultTimeSlice);
	friend class PCB;
	friend int main(int argc, char *argv[]);
	virtual void run(){ };

private:
	PCB *myPCB;
																	

};

void dispatch();
#endif