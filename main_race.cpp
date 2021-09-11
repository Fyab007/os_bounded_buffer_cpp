#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>

#include "defs.h"

int buffer[BUF_SIZE];
int count = 0;
int item_id = 900; // unique item id
int put_index = 0; // producer puts an item at this index
int get_index = 0; // consumer gets an item from this index

sem_t buffer_access;

extern void* producer(void* param);
extern void* consumer(void* param);

int main(int argc, char **argv) {

	if (argc != 2) {
		printf("Usage: %s loop_count\n", argv[0]);
		exit(1);
	}

	sem_init(&buffer_access, 0, 1);

	pthread_t t_producer1;
	pthread_t t_producer2;
	pthread_t t_consumer;

	pthread_attr_t attr;
	pthread_attr_init(&attr);

	pthread_create(&t_producer1, &attr, producer, (void *) argv[1]);
	pthread_create(&t_consumer, &attr, consumer, (void *) argv[1]);

	pthread_join(t_producer1, NULL);
	pthread_join(t_consumer, NULL);

}