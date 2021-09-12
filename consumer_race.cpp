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

extern sem_t buffer_access;

void* consumer(void* p) {
	printf("consumer started with count = %d\n", count);
	parameters* params = (parameters*) p;
	int loop = params->loop_count;

	std::ofstream file;
	file.open(params->filename);

	for (int i = 0; i < loop; i++) {

		while (count <= 0) ; // wait

		int consume_item_id = buffer[get_index];
		get_index = ++get_index % BUF_SIZE;
		printf("%d - consumer(%d)\n", i, consume_item_id);
		file << consume_item_id << std::endl;

		// To simulate what CPU instructions do for --count
		int reg = count;
		--reg;
		usleep(rand() % 1000000); // to increase probability of race condition
		count = reg;
	}
	file.close();
	// pthread_exit(0);
	exit(0); // whole program quits
}