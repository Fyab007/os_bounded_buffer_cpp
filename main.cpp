#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <string.h>

#include "defs.h"

int buffer[BUF_SIZE];
int count = 0;
int item_id = 700; // unique item id
int put_index = 0; // producer puts an item at this index
int get_index = 0; // consumer gets an item from this index

// mutex to access the buffer
pthread_mutex_t mutex;
// counting semaphores for buffer resources
sem_t full;
sem_t empty;

extern void* producer(void* param);
extern void* consumer(void* param);

int main(int argc, char **argv) {

	if (argc != 2) {
		printf("Usage: %s loop_count\n", argv[0]);
		exit(1);
	}

	pthread_mutex_init(&mutex, NULL);
	sem_init(&empty, 0, BUF_SIZE);
	sem_init(&full, 0, 0);

	pthread_t t_producer1;
	pthread_t t_producer2;
	pthread_t t_consumer;

	pthread_attr_t attr;
	pthread_attr_init(&attr);

	// pass argv[1] and filename to thread
	Parameters* p_params = new Parameters;
	p_params->loop_count = atoi(argv[1]);
	strcpy(p_params->filename, "prod.txt");
	pthread_create(&t_producer1, &attr, producer, (void *) p_params);

	Parameters* c_params = new Parameters;
	c_params->loop_count = atoi(argv[1]);
	strcpy(c_params->filename, "cons.txt");
	pthread_create(&t_consumer, &attr, consumer, (void *) c_params);

	pthread_join(t_producer1, NULL);
	pthread_join(t_consumer, NULL);

}