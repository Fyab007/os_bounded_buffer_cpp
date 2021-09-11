#include <semaphore.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

#include "defs.h"

extern int buffer[BUF_SIZE];
extern int item_id;
extern int count;
extern int put_index;
extern int get_index;

const int LOOP = 100;

extern sem_t buffer_access;

void* producer(void* param) {
	printf("producer started with count = %d\n", count);
	for (int i = 0; i < LOOP; i++) {

		while (count >= BUF_SIZE) ; // wait

		buffer[put_index] = item_id;
		printf("P[%d]\n", item_id);
		item_id++;
		put_index = ++put_index % BUF_SIZE;

		// To simulate what CPU instructions do for ++count
		int reg = count;
		++reg;
		usleep(rand() % 200000); // to increase probability of race condition
		count = reg;

	}
}