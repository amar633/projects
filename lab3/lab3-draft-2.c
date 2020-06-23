/*
 * lab3.c
 *
 *  Created on: Jun 17, 2020
 *      Author: Yasmine Goudjil
 */

#include <pthread.h>
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <math.h>

#define MAX_SAMPLE_SIZE 100

#define STAT_SUM 0
#define STAT_AVG 1
#define STAT_MAX 2
#define STAT_MIN 3
#define STAT_MED 4
#define STAT_STD 5

/* this data is shared by the thread(s) */
int num[MAX_SAMPLE_SIZE];
int sum, min, max, size;
float avg, med, std;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

void* runner(void *param); /* The runner performed by the threads*/

void num_sort();

int main() {
	int lower = 0, upper = 100, ops_0, ops_1, ops_2, ops_3, ops_4, ops_5;

	// Use current time as
	// seed for random generator
	srand(time(0));

	printf("\n\nEnter sample size: ");
	scanf(" %d", &size);
	if (size <= 0) {
		printf("\nSize must be a positive number !\n");
		exit(0);
	}
	printf("\nRandom NUmber Generation\n========================\n");
	for (int i = 0; i < size; i++) {
		num[i] = (rand() % (upper - lower + 1)) + lower;
		printf("%d --> %d  ", i, num[i]);
	}
	printf("\n\n");

	pthread_t tid_sum, tid_avg, tid_min, tid_max, tid_med, tid_std; /* the int to identify each thread*/
	pthread_attr_t attr; /* set of attributes for the thread */

	/* get the default attributes */
	pthread_attr_init(&attr);

	/* create the thread */
	ops_4 = STAT_MED;
	pthread_create(&tid_med, &attr, runner, &ops_4);
	ops_0 = STAT_SUM;
	pthread_create(&tid_sum, &attr, runner, &ops_0);
	ops_3 = STAT_MIN;
	pthread_create(&tid_min, &attr, runner, &ops_3);
	ops_2 = STAT_MAX;
	pthread_create(&tid_max, &attr, runner, &ops_2);
	ops_1 = STAT_AVG;
	pthread_create(&tid_avg, &attr, runner, &ops_1);
	ops_5 = STAT_STD;
	pthread_create(&tid_std, &attr, runner, &ops_5);

	/* now wait for the thread to exit */
	pthread_join(tid_sum, NULL);
	pthread_join(tid_avg, NULL);
	pthread_join(tid_min, NULL);
	pthread_join(tid_max, NULL);
	pthread_join(tid_med, NULL);
	pthread_join(tid_std, NULL);

	printf("\nsum_value = %d\n", sum);
	printf("\nmean_value = %5.2f\n", avg);
	printf("\nminimum_value = %d\n", min);
	printf("\nmaximum_value = %d\n", max);
	printf("\nmedian_value = %5.2f\n", med);
	printf("\nstandard_deviation= %5.2f\n", std);
}

void* runner(void *param) {
	int i, stat_val = *(int*) param;
	printf("\nstat_val=%d ", stat_val);
	if (stat_val == STAT_SUM) {
		pthread_mutex_lock(&mutex);
		sum = 0;
		printf("\nThread sum\n");
		for (i = 0; i < size; i++)
			sum += num[i];
		printf("\nsum_value = %d\n", sum);
		pthread_mutex_unlock(&mutex);
	} else if (stat_val == STAT_AVG) {
		int ttl = 0;
		printf("\nThread avg\n");
		for (i = 0; i < size; i++)
			ttl += num[i];
		avg = ttl / (float) size;
		printf("\nmean_value = %5.2f\n", avg);
	} else if (stat_val == STAT_MAX) {
		int temp = num[0];
		printf("\nThread max\n");
		for (i = 0; i < size; i++)
			if (temp < num[i])
				temp = num[i];
		max = temp;
		printf("\nmaximum_value = %d\n", max);
	} else if (stat_val == STAT_MIN) {
		int temp = num[0];
		printf("\nThread min\n");
		for (i = 0; i < size; i++)
			if (temp > num[i])
				temp = num[i];
		min = temp;
		printf("\nminimum_value = %d\n", min);
	} else if (stat_val == STAT_MED) {
		printf("\nThread med\n");
		num_sort();
		// if number of elements are even
		if (size % 2 == 0)
			med = (num[(size - 1) / 2] + num[size / 2]) / 2.0;
		// if number of elements are odd
		else
			med = num[size / 2];
		printf("\nmedian_value = %5.2f\n", med);
	} else if (stat_val == STAT_STD) {
		int temp = num[0], avg_1, ttl_1 = 0;
		printf("\nThread STD\n");
		for (i = 0; i < size; i++)
			ttl_1 = ttl_1 + num[i];
		avg_1 = ttl_1 / (float) size;
		ttl_1 = 0;
		for (i = 0; i < size; i++)
			ttl_1 = ttl_1 + pow((num[i] - avg_1), 2);
		std = sqrt(ttl_1 / size);
		printf("\nstandard_deviation= %5.2f\n", std);
	} else {
		printf("\nStatistic not implemented yer!");
	}
}

/* function to sort the array in ascending order */
void num_sort() {
// declare some local variables
	int i = 0, j = 0, temp = 0;
	for (i = 0; i < size; i++) {
		for (j = 0; j < size - 1; j++) {
			if (num[j] > num[j + 1]) {
				temp = num[j];
				num[j] = num[j + 1];
				num[j + 1] = temp;
			}
		}
	}
	printf("\nThe array after sorting is..\n");
	for (i = 0; i < size; i++) {
		printf("\num[%d] : %d", i, num[i]);
	}
}
