#ifndef _TIMER_H_
#define _TIMER_H_


extern volatile unsigned preemptionDisabled;
extern volatile char switchContextOnRequest;
extern volatile char explicitCallForTimer;

void tick();
void interrupt timer(...);
void init();
void restore();
unsigned static long timeCoutner;

#endif