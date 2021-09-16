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

extern void* producer(void *);
extern void* consumer(void *);

int main(int argc, char **argv) {

	if (argc != 2) {
		printf("Usage: %s loop_count\n", argv[0]);
		exit(1);
	}

	int loop_count = atoi(argv[1]);
	if (loop_count == 0) {
		printf("Usage: %s max_loop_count\n", argv[0]);
		exit(1);
	}

	pthread_t t_producer;
	pthread_t t_consumer;

	pthread_attr_t attr;
	pthread_attr_init(&attr);

	// pass loop_count and filename to thread
	parameters* p_params = new parameters;
	p_params->loop_count = loop_count;
	p_params->filename = (char *) "prod_race.txt";

	parameters* c_params = new parameters;
	c_params->loop_count = loop_count;
	c_params->filename = (char *) "cons_race.txt";

	pthread_create(&t_producer, &attr, producer, (void *) p_params);
	pthread_create(&t_consumer, &attr, consumer, (void *) c_params);

	pthread_join(t_producer, NULL);
	pthread_join(t_consumer, NULL);

}