#include <semaphore.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

#include <fstream> // C++

#include "defs.h"

extern int buffer[BUF_SIZE];
extern int item_id;
extern int count;
extern int put_index;
extern int get_index;

extern pthread_mutex_t mutex;
extern sem_t full;
extern sem_t empty;

void* producer(void* params) {
	printf("producer started with count = %d\n", count);
	Parameters* passed_params = (Parameters *) params;
	int loop = passed_params->loop_count;

	std::ofstream file;
	file.open((char*) passed_params->filename);

	for (int i = 0; i < loop; i++) {

		/* Acquire Empty Semaphore */
		sem_wait(&empty);

		/* Acquire mutex lock to protect buffer */
		pthread_mutex_lock(&mutex);

		// enters critical section
		buffer[put_index] = item_id;
		printf("%d - Prod[%d]\n", i, item_id);
		file << item_id << std::endl;
		item_id++;
		put_index = ++put_index % BUF_SIZE;

		// To simulate what CPU instructions do for ++count
		int reg = count;
		++reg;
		usleep(rand() % 200000); // to increase probability of race condition
		count = reg;

		// leaves critical section
		/* Release mutex lock and full semaphore */
		pthread_mutex_unlock(&mutex);
    	sem_post(&full);

		usleep(rand() % 200000);

	}

	file.close();
	pthread_exit(0);
}