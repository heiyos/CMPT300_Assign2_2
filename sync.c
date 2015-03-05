/*
 * NAME, etc.
 *
 * sync.c
 *
 */

#define _REENTRANT

#include "sync.h"

#define locked 1
#define unlocked 0

/*
 * Spinlock routines
 */


int my_spinlock_init(my_spinlock_t *mutex){
	mutex -> lock = unlocked;
	return 0;
}

int my_spinlock_destroy(my_spinlock_t *mutex){
	//delete mutex;
	return 0;
}

int my_spinlock_unlock(my_spinlock_t *mutex){
	current = syscall(SYS_gettid);
	if (owner == current){
		mutex -> lock = 0;
		return 0;
	} else {
		return -1;
	}
}

int my_spinlock_lockTAS(my_spinlock_t *mutex){
	int lock_status = mutex -> lock;
	if (lock_status == unlocked){
		owner = syscall(SYS_gettid);
		tas(&mutex -> lock);
		return 0;
	} else if (syscall(SYS_gettid) == owner){
		return 0;
	} else {
		return -1;
	}
	
}


int my_spinlock_lockTTAS(my_spinlock_t *mutex){
	/*int temp = mutex -> lock;
	if (temp == 1){
		if (temp == 0){
			mutex -> lock = 1;
		}
	} else {
		mutex -> lock = 0;
	}
	return 0;*/
}

int my_spinlock_trylock(my_spinlock_t *mutex){

}


/*
 * Mutex routines
 */

int my_mutex_init(my_mutex_t *mutex)
{
}

int my_mutex_destroy(my_mutex_t *mutex)
{
}

int my_mutex_unlock(my_mutex_t *mutex)
{
}

int my_mutex_lockTAS(my_mutex_t *mutex)
{
}


int my_mutex_lockTTAS(my_mutex_t *mutex)
{
}

int my_mutex_trylock(my_mutex_t *mutex)
{
}


