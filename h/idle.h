#ifndef _IDLE_H_
#define _IDLE_H_

#include "thread.h"

class IdleThread: public Thread {
public:
	IdleThread();
protected:
	void run();
};

#endif

