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
	//free(mutex);
	return 0;
}

int my_spinlock_unlock(my_spinlock_t *mutex){
	mutex -> lock = 0;
	return 0;
}

int my_spinlock_lockTAS(my_spinlock_t *mutex){
	while (tas(&mutex -> lock)){
		continue;
	}
	return 0;
	
}


int my_spinlock_lockTTAS(my_spinlock_t *mutex){
	current = pthread_self();
	while (1){
		while (mutex -> lock == locked/* || (current != owner)*/){
			continue;
		}
		if (!tas(&mutex -> lock)/* || current == owner*/){
			owner = current;
			return 0;
		}
	}
	return -1;
}

int my_spinlock_trylock(my_spinlock_t *mutex){
	if (tas(&mutex -> lock)){
		return -1;
	} else {
		return 0;
	}
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


