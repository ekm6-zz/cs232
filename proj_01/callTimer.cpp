/* callTimer.cpp runs two sysyem calls
 *  -fork() which creates a new UNIX process, and
 *  -pthread_create() which creates a new POSIX thread.
 * It also average time to run each Process
 *
 *  Created on: Feb 7, 2019
 *  Author: Enoch Mwesigwa
 */

#include "NanoTimer.h"
#include <iostream>
#include <string>
#include <string.h>
#include <cstdlib>
#include <unistd.h>
#include <pthread.h>
#include  <sys/types.h>
#include  <sys/ipc.h>
#include  <sys/shm.h>
using namespace std;

/*Print hello
 * @param: thread ID
 * PostCondition: displays "hello" along with thread ID
 */
void *PrintHello(void *threadid) {
	long tid;
	tid = (long) threadid;
	cout << "Hello from child thread (TID = " << tid << ")" << endl;
	pthread_exit(NULL);
}

/* CallTimer
 * @param: int, bool, bool
 * Precondition: variables contain the # of times a a thread or proccess will
 * be created as well whether or not they'll be created
 * Post Condition: will display the average run time for the specified functions
 */
void callTimer(int counter, bool process, bool thread) {
	NanoTimer timer;
	// create shared memory key
	key_t key = ftok("shmfile", 1);

	// shmget returns an identifier in shmid (will be used to hold process run time)
	double shmidProcess = shmget(key, 4 * sizeof(double), IPC_CREAT | 0666);\
	//will hold thread run time
	double tTime;

	if (process == true) {
		for (int i = 0; i < counter; i++) {
			timer.start();
			// create fork
			pid_t PID = fork();
			timer.stop();
			double splitTime = timer.getTotalTime();
			if (PID == 0) {
				// shmat to attach to shared memory
				double *pTime = (double*) shmat(shmidProcess, (void*) 0, 0);

				*pTime += splitTime;

				//detach from shared memory
				shmdt(pTime);

				exit(0);
			}
			cout << "Hello from the child process (PID = " << PID << ")"
					<< endl;

		}

		timer.reset();
		double *pTime = (double*) shmat(shmidProcess, (void*) 0, 0);
		*pTime /= counter;
		cout << "Average Split time for fork() was " << *pTime << endl;
		shmdt(pTime);

	}

	if (thread == true) {

		for (int i = 0; i < counter; i++) {
			pthread_t threads[2];
			int rc;
			timer.start();
			rc = pthread_create(&threads[1], NULL, PrintHello, (void *) i);
			timer.stop();
			tTime += timer.getTotalTime();

			//check if thread was created
			if (rc) {
				cout << "Error:unable to create thread," << rc << endl;
				exit(-1);
			}
		}

		tTime /= counter;
		cout << "Average Split time for Thread() was " << tTime << endl;
	}

}

/* Main.cpp
 * @param: int, char
 * Precondition: variables contain arguements for the code
 * Post Condition: will run the specified arguements or display and error.
 */
int main(int argc, char* argv[]) {
	bool process, thread = false;
	string arg;

	int counter;
	for (int i = 1; i < argc; i++) {
		arg = argv[i];

		if (arg.substr(0, 2) == "-r") {
			counter = atoi(arg.substr(2).c_str());
		}

		if (arg == "-p" || arg == "-process") {
			process = true;
		}

		if (arg == "-thread" || arg == "-t") {
			thread = true;
		}

	}

	if (process == false && thread == false) {
		cerr << "Usage Error" << endl;
		exit(0);

	}

	callTimer(counter, process, thread);
	return 0;
}
