#include "ivtentry.h"
#include "locks.h"
#include "event.h"
#include <dos.h>

IVTEntry* IVTEntry::ledgerEntries[NUM_OF_ENTRIES] = {0};

IVTEntry::IVTEntry(IVTNo numOfEntry, void interrupt (*newRoutine)(...)){
	entryNumber = numOfEntry;
	event = 0;
	INTR_LOCK
	oldRoutine = getvect(numOfEntry);
	setvect(numOfEntry, newRoutine);
	ledgerEntries[numOfEntry] = this;
	INTR_UNLOCK
}

IVTEntry::~IVTEntry(){
	INTR_LOCK
	setvect(entryNumber, oldRoutine);
	INTR_UNLOCK
}

IVTEntry* IVTEntry::getEntry(IVTNo numOfEntry){
	return IVTEntry::ledgerEntries[numOfEntry];
}

void IVTEntry::signal(IVTNo numOfEntry){
	if(ledgerEntries[numOfEntry]->event != 0)
		ledgerEntries[numOfEntry]->event->signal();
}
void IVTEntry::callOldInterruptRoutine(IVTNo numOfEntry){
	ledgerEntries[numOfEntry]->oldRoutine();
}
void IVTEntry::addEvent(IVTNo numOfEntry, Event *event){
	ledgerEntries[numOfEntry]->event = event;
}



