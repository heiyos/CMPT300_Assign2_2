#include "main.h"

void *fnC() {
    int i;
    for(i=0;i<1000000;i++) {   
        c++;
    }   
}


pthread_mutex_t count_mutex;

void *pthreadMutexTest() {
	int i;
	for(i=0;i<numItterations;i++) { 
		pthread_mutex_lock(&count_mutex);
		c++;
		pthread_mutex_unlock(&count_mutex);	
	}   
}

int runTest(int testID) {

	/*You must create all data structures and threads for you experiments*/

	if (testID == 0 || testID == 1 ) {/*Pthread Mutex*/
		c=0;
		struct timespec start;
		struct timespec stop;
		unsigned long long result; //64 bit integer

		pthread_t *threads = (pthread_t* )malloc(sizeof(pthread_t)*numThreads);	
		int i;
		int rt;

		clock_gettime(CLOCK_MONOTONIC, &start);
		for(i=0;i<numThreads;i++) {
	
			if( rt=(pthread_create( threads+i, NULL, &pthreadMutexTest, NULL)) ) {
				printf("Thread creation failed: %d\n", rt);
				return -1;	
			}
		}
	
		/* Wait for all threads to finish */
		for(i=0;i<numThreads;i++) {
			 pthread_join(threads[i], NULL);
		}
		clock_gettime(CLOCK_MONOTONIC, &stop);

		printf("Threaded Run Pthread (Mutex) Total Count: %d\n", c);
		result=timespecDiff(&stop,&start);
		printf("Pthread Mutex time(ms): %llu\n",result/1000000);
	}

	/* Pthread Spinlock */
	else if(testID == 0 || testID == 2) {
	/*Pthread Spinlock goes here*/
	}

	/*MySpinlockTAS*/
	else if(testID == 0 || testID == 3) {
	/* mySpinlock TAS goes here*/
	}

	/*....you must implement the other tests....*/

	return 0;
}

int testAndSetExample() {
	/* Test is set to 0 */
	volatile long test = 0;
	printf("Test before atomic OP:%d\n",test);
	tas(&test);
	printf("Test after atomic OP:%d\n",test);
}

int processInput(int argc, char *argv[]) {

/*testid: 0=all, 1=pthreadMutex, 2=pthreadSpinlock, 3=mySpinLockTAS, 4=mySpinLockTTAS, 5=myMutexTAS, 6=myMutexTTAS*/

	char buffer[512];
	char *pointer = buffer;
	char *command;
	memset(buffer, 0, sizeof(buffer));

	printf("Input Parameters: ");
        fgets(buffer, sizeof(buffer), stdin);

	numThreads=4;
	numItterations=1000000;
	testID=0;

	printf("buffer: %s\n", buffer);
	command = strtok_r(pointer, " \n\t", &pointer);
	printf("buffer: %s\n", buffer);
	printf("command: %s\n", command);

	while (command = strtok_r(pointer, " \n\t", &pointer)) {
		
		//if (strcmp(command, "-t") == 0) {
			//command = strtok_r(pointer, " \n\t", &pointer);
			//numThreads = atoi(command);
		//}
	}
	
	return 0;
}


int main(int argc, char *argv[]) {


	printf("\nUsage of: %s \n", argv[0]);
	printf("Please use the following format: -t #threads -i #itterations -d testid\n", argv[0]);
	printf("If a parameter is missed default values will be used. \n", argv[0]);
	printf("testid: 0=all, 1=pthreadMutex, 2=pthreadSpinlock, 3=mySpinLockTAS, 4=mySpinLockTTAS, 5=myMutexTAS, 6=myMutexTTAS\n");	
	
	//testAndSetExample(); //Uncomment this line to see how to use TAS
	
	processInput(argc,argv);
	runTest(testID);
	return 0;
}
