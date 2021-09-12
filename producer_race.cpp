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

extern sem_t buffer_access;

void* producer(void* p) {
	printf("producer started with count = %d\n", count);
	parameters* params = (parameters *) p;
	int loop = params->loop_count;

	std::ofstream file;
	file.open(params->filename);

	for (int i = 0; i < loop; i++) {

		while (count >= BUF_SIZE) ; // wait

		buffer[put_index] = item_id;
		printf("%d - P[%d]\n", i, item_id);
		file << item_id << std::endl;
		item_id++;
		put_index = ++put_index % BUF_SIZE;

		// To simulate what CPU instructions do for ++count
		int reg = count;
		++reg;
		usleep(rand() % 200000); // to increase probability of race condition
		count = reg;

	}
	file.close();

	// the whole program quits
	// pthread_exit(0);
	exit(0); // consumer may not complete the loop due to race condition
}