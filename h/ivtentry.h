#ifndef _IVTENTRY_H_
#define _IVTENTRY_H_

typedef unsigned char IVTNo;
#define NUM_OF_ENTRIES 256
class Event;
class IVTEntry{
public:
	IVTEntry(IVTNo numOfEntry, void interrupt (*newRoutine)(...));
	~IVTEntry();

	static IVTEntry *ledgerEntries[];
	static IVTEntry *getEntry(IVTNo numOfEntry);
	static IVTEntry *getEntry();
	static void signal(IVTNo numOfEntry);
	static void callOldInterruptRoutine(IVTNo numOfEntry);
	static void addEvent(IVTNo numOfEntry, Event *event);
private:
	IVTNo entryNumber;
	void interrupt (*oldRoutine)(...);
	Event *event;

};

#endif
