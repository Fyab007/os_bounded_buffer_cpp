#include <semaphore.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

#include <fstream>

#include "defs.h"

extern int buffer[BUF_SIZE];
extern int item_id;
extern int count;
extern int put_index;
extern int get_index;

extern pthread_mutex_t mutex;
extern sem_t full;
extern sem_t empty;

void* consumer(void* p) {
	printf("consumer started with count = %d\n", count);
	parameters* params = (parameters*) p;
	int loop = params->loop_count;

	std::ofstream file;
	file.open(params->filename);

	for (int i = 0; i < loop; i++) {

		/* Acquire Full Semaphore */
		sem_wait(&full);

		/* Acquire mutex lock to protect buffer */
		pthread_mutex_lock(&mutex);

		// enters critical section
		int consume_item_id = buffer[get_index];
		get_index = ++get_index % BUF_SIZE;
		printf("  %d - Consumer(%d)\n", i, consume_item_id);
		file << consume_item_id << std::endl;

		// To simulate what CPU instructions do for --count
		int reg = count;
		--reg;
		usleep(rand() % 1000000); // to increase probability of race condition
		count = reg;

		// leaves critical section
		/* Release mutex lock and empty semaphore */
		pthread_mutex_unlock(&mutex);
    	sem_post(&empty);

		usleep(rand() % 400000);
	}

	file.close();
	pthread_exit(0);
}