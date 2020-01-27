#ifndef _LOCKS_H_
#define _LOCKS_H_
#include "timer.h"

#define INTR_LOCK asm {\
				pushf;\
				cli;\
}

#define INTR_UNLOCK asm popf;

#define PREEMPT_LOCK ++preemptionDisabled;

#define PREEMPT_UNLOCK --preemptionDisabled;\
						if(!preemptionDisabled && switchContextOnRequest)\
							dispatch();\
						else ;
#endif










































