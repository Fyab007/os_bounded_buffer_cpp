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

extern sem_t buffer_access;

void* consumer(void* param) {
	printf("consumer started with count = %d\n", count);
	int loop = atoi( (char *) param);
	for (int i = 0; i < loop; i++) {

		while (count <= 0) ; // wait

		int consume_item_id = buffer[get_index];
		get_index = ++get_index % BUF_SIZE;
		printf("consumer(%d)\n", consume_item_id);

		// To simulate what CPU instructions do for --count
		int reg = count;
		--reg;
		usleep(rand() % 1000000); // to increase probability of race condition
		count = reg;
	}
	exit(0);
}