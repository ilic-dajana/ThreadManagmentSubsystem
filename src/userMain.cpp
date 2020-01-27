// #include<iostream.h>

// #include"timer.h"
// #include "thread.h"
// #include "locks.h"
// #include "event.h"
// #include "semaphor.h"

// //volatile long global = 0;
// Semaphore mutex(1);
// Semaphore first(1);
// Semaphore second(0);

// PREPAREENTRY(9, 1)

// class KeyListener: public Thread {

// protected:
// 	void run() {
// 		Event *event = new Event(9);
// 		while (1) {
// 			mutex.wait(1);
// 			cout << "waiting..." << endl;
// 			mutex.signal();

// 			event->wait();

// 			mutex.wait(1);
// 			cout << "Key pressed..." << endl;
// 			mutex.signal();

// 				mutex.wait(1);
// 			cout << "waiting..." << endl;
// 			mutex.signal();

// 			event->wait();
// 				mutex.wait(1);
// 			cout << "Key pressed..." << endl;
// 			mutex.signal();

// 		}
// 	}
// };

// void tick(){

// }
// class Print2: public Thread{
// private:
// 	int id;
// 	const char* text;
// public:
// 	Print2(int idd, const char* txt): Thread(4096, 2), id(idd), text(txt) { }
// protected:
// 	void run(){
// 		while(1){
// 			second.wait(1);
// 			mutex.wait(1);
// 			cout<< text <<endl;
// 			mutex.signal();
// 			Thread::sleep(20);
// 			first.signal();
// 		}
// 	}
// };
// class Print1: public Thread{
// private:
// 	int id;
// 	const char* text;
// public:
// 	Print1(int idd, const char* txt):Thread(4096, 2), id(idd), text(txt) {  }
// protected:
// 	void run(){
// 		while(1){
// 			first.wait(1);
// 			mutex.wait(1);
// 			cout<< text <<endl;
// 			mutex.signal();
// 			Thread::sleep(20);
// 			second.signal();
// 		}

// 	}
// };

// class Spawner: public Thread{
// private:
// 	int nthreads;
// public:
// 	Spawner(int n):Thread(2048, 2), nthreads(n){ }
// protected:
// 	void run(){
// 		Thread **t = 0;
// 		int i;

// 		t = new Thread *[nthreads];

// 		for (i = 0; i < nthreads; ++i) {
// 			t[i] = new Print1(i, "ja");
// 			t[i]->start();
// 		}

// 		for (i = 0; i < nthreads; ++i) {
// 			t[i]->waitToComplete();
// 		}
// 	}

// };



// int userMain(int argc, char* argv[]){

// 	// Thread *spawner = new Spawner(5);
// 	// Thread* th1 = new Print1(1, "Da l' si ikada mene volela");
// 	// Thread* th2 = new Print2(2, "Kao tebe ja");
	
// 	// th1->start();
// 	// th2->start();
// 	// th1->waitToComplete();

// 	// spawner->start();
// 	// spawner->waitToComplete();

	
// 	KeyListener *keyListener = new KeyListener();


// 	keyListener->start();
// 	keyListener->waitToComplete();

// 	return 0;
// }