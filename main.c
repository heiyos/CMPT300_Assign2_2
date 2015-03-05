#include <string.h>
#include "main.h"

void *fnC() {
    int i;
    for(i=0;i<1000000;i++) {   
        c++;
    }   
}

/* For the PThread Mutex Test */
pthread_mutex_t count_mutex;

void *pthreadMutexTest() {
	int i;
	printf("Starting test 1\n");
	for(i=0;i<numItterations;i++) { 
		pthread_mutex_lock(&count_mutex);
		c++;
		printf("Iteration Number: %d\n", c);
		pthread_mutex_unlock(&count_mutex);	
	}   
}

/* For the PThread Mutex Test */
pthread_spinlock_t count_spinlock;

void *pthreadSpinlockTest() {
	int i;
	printf("Starting Test 2\n");
	for(i=0;i<numItterations;i++) {
		printf("here?\n"); 
		if (pthread_spin_lock(&count_spinlock)!=0){
			printf("lock failed\n");
		}
		c++;
		printf("Iteration Number: %d\n", c);
		pthread_spin_unlock(&count_spinlock);	
	}   
}

/* Run the tests */
int runTest(int testID) {

	/*Pthread Mutex*/
	if (testID == 0 || testID == 1 ) {
		printf("Start of TestID 1 - Pthread Mutex\n");
		c=0;
		struct timespec start;
		struct timespec stop;
		unsigned long long result;

		pthread_t *threads = (pthread_t* )malloc(sizeof(pthread_t)*numThreads);	
		int i;
		int rt;

		clock_gettime(CLOCK_MONOTONIC, &start);
		for(i=0;i<numThreads;i++) {
	
			if( rt=(pthread_create(threads+i, NULL, &pthreadMutexTest, NULL)) ) {
				printf("Thread creation failed: %d\n", rt);
				return -1;	
			}
		}
	
		for(i=0;i<numThreads;i++) {
			 pthread_join(threads[i], NULL);
		}
		clock_gettime(CLOCK_MONOTONIC, &stop);

		printf("Threaded Run Pthread (Mutex) Total Count: %d\n", c);
		result=timespecDiff(&stop,&start);
		printf("Pthread Mutex time(ms): %llu\n\n",result/1000000);
	}

	/* Pthread Spinlock */
	if(testID == 0 || testID == 2) {
		printf("Start of TestID 2 - Pthread Spinlock\n");
		c=0;
		struct timespec start;
		struct timespec stop;
		unsigned long long result;

		pthread_t *threads = (pthread_t* )malloc(sizeof(pthread_t)*numThreads);	
		int i;
		int rt;

		clock_gettime(CLOCK_MONOTONIC, &start);
		for(i=0;i<numThreads;i++) {
	
			if( rt=(pthread_create(threads+i, NULL, &pthreadSpinlockTest, NULL)) ) {
				printf("Thread creation failed: %d\n", rt);
				return -1;	
			}
		}
	
		for(i=0;i<numThreads;i++) {
			 pthread_join(threads[i], NULL);
		}
		clock_gettime(CLOCK_MONOTONIC, &stop);

		printf("Threaded Run Pthread (Spinlock) Total Count: %d\n", c);
		result=timespecDiff(&stop,&start);
		printf("Pthread Spinlock time(ms): %llu\n",result/1000000);
	}

	/* MySpinlockTAS */
	if(testID == 0 || testID == 3) {

	}

	/* MySpinlockTTAS */
	if(testID == 0 || testID == 4) {

	}

	/* MyMutexTAS */
	if(testID == 0 || testID == 5) {

	}

	/* MyMutexTTAS */
	if(testID == 0 || testID == 6) {

	}

	return 0;
}

/* Process user input */
int processInput(int argc, char *argv[]) {

	char buffer[512];
	char *pointer = buffer;
	char *command;
	memset(buffer, 0, sizeof(buffer));

	printf("Input Parameters: ");
        fgets(buffer, sizeof(buffer), stdin);

	numThreads=4;
	numItterations=1000000;
	testID=0;

	while (command = strtok_r(pointer, " \n\t", &pointer)) {
		
		if (strcmp(command, "-t") == 0) {
			command = strtok_r(pointer, " \n\t", &pointer);			
			if (atoi(command) > 0) {
				numThreads = atoi(command);
			} else {
				printf("Invalid Thread count. Thead count must be an integer greater than 0.\n");
			}
		} else if (strcmp(command, "-i") == 0) {
			command = strtok_r(pointer, " \n\t", &pointer);
			if (atoi(command) > 0) {
				numItterations = atoi(command);
			} else {
				printf("Invalid Iteration count. Iteration count must be an integer greater than 0.\n");
			}
		} else if (strcmp(command, "-d") == 0) {
			command = strtok_r(pointer, " \n\t", &pointer);
			if (atoi(command) <= 6 && atoi(command) >= 0) {
				testID = atoi(command);
			} else {
				printf("Invalid TestID. Tedt ID must be between 0 and 6\n");
			}
		} else {
			printf("Command '%s' not recognized.\n", command);
		}
	}

	printf("Number of threads: %d\n", numThreads);
	printf("Number of ierations: %d\n", numItterations);
	printf("Test ID: %d\n\n", testID);
	
	return 0;
}

/* Main Program */
int main(int argc, char *argv[]) {


	printf("\nUsage of: %s \n", argv[0]);
	printf("Please use the following input format: -t #threads -i #itterations -d testid\n", argv[0]);
	printf("If a parameter is missed default values will be used. \n", argv[0]);
	printf("testid:\n    0 = all\n    1 = pthreadMutex\n    2 = pthreadSpinlock\n    3 = mySpinLockTAS\n    4 = mySpinLockTTAS\n    5 = myMutexTAS\n    6 = myMutexTTAS\n");	
	
	processInput(argc,argv);
	runTest(testID);
	return 0;
}
