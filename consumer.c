/*
Solution to Producer Consumer Problem
By, Jason Abounader
For Operating Systems Class at Kent State
*/


#include <stdio.h>
#include <unistd.h>
#include <semaphore.h>
#include <fcntl.h>
#include <pthread.h>
#include <sys/mman.h>
#include <sys/shm.h>

//local names to identify semaphores
#define FULLNAME "/fullsem"
#define EMPTYNAME "/emptysem"

#define TABLENAME "/shm_table"
//table will hold 2 integers
#define SIZE 2
#define TABLESIZE (SIZE * sizeof(int))

//Having both full and empty semaphores is needed in order to swap off turns to produce and consume between processes
sem_t *full;
sem_t *empty;

//serves as buffer for producer consumer problem
int *table;

void *consume() {
	
	//Empties buffer 10 times as demonstration
	for(int i = 0; i < 10; i++) {
		
		//Decrements semaphore blocks until post
		sem_wait(full);
		printf("\n~Consumer enters critical section\n");
		
		//1's are changed to 0's to emulate "consuming an item"
		for(int x = 0; x < SIZE; x++) {
			if(table[x] == 1) {
				table[x] = 0;
				printf("Item consumed at index %d\n", x);
				printf("[ %d , %d ]\n",table[0],table[1]);
			}
			
			
		}

		sleep(1); 
		printf("~Consumer exits critical section\n");

		//increments semaphore which allows access
		sem_post(empty);

	}
	
	return NULL;

}

int main() {
	printf("\n");
	
	//define semaphores which will serve as a mutex lock for critical operations
	full = sem_open(FULLNAME,O_RDWR);
	empty = sem_open(EMPTYNAME,O_RDWR);

	//if failed unlink semaphore (can happen when execution doesn't complete)
	if(full == SEM_FAILED || empty == SEM_FAILED) {
		printf("Consumer: FAILURE in creating semaphore\n");
		if(full == SEM_FAILED) {
			sem_unlink(FULLNAME);
		} 
		if(empty == SEM_FAILED) {
			sem_unlink(EMPTYNAME);
		}
		
		return(-1);
		
	} 

	int fd = shm_open(TABLENAME, O_RDWR, 0644);
	if(fd < 0) {
		printf("Producer: shm_error");
		return(-1);
	}
	
	//maps into shared memory
	table = (int *)mmap(0,TABLESIZE,PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
	

	//Creates andn begins thread
	pthread_t thread_id;
	pthread_create(&thread_id, NULL, consume, NULL);

	
	pthread_join(thread_id, NULL);
	
	//unlink semaphores and shared memory
	sem_close(full);
	sem_unlink(FULLNAME);
	sem_close(empty);
	sem_unlink(EMPTYNAME);

	close(fd);
	shm_unlink(TABLENAME);

	return(0);

}


