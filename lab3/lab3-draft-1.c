#include <pthread.h>
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#define MAX_SAMPLE_SIZE 100

/* this data is shared by the thread(s) */
int num[MAX_SAMPLE_SIZE];
int sum, min, max, size;
float avg, med;

void* runner_sum(void *param); /* the thread  for the sum*/
void* runner_avg(void *param); /* the thread  for mean value */
void* runner_min(void *param); /* The thread for the minmum value */
void* runner_max(void *param); /* The thread for the maximum value */
void* runner_med(void *param); /* The thread for the median value */
void num_sort();

int main(int argc, char *argv[]) {
	int lower = 0, upper = 100;

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

	pthread_t tid_sum, tid_avg, tid_min, tid_max, tid_med; /* the int to identify each thread*/
	pthread_attr_t attr; /* set of attributes for the thread */

	/* get the default attributes */
	pthread_attr_init(&attr);

	/* create the thread */

	pthread_create(&tid_sum, &attr, runner_sum, argv[1]);
	pthread_create(&tid_min, &attr, runner_min, argv[1]);
	pthread_create(&tid_max, &attr, runner_max, argv[1]);
	pthread_create(&tid_avg, &attr, runner_avg, argv[1]);
	pthread_create(&tid_med, &attr, runner_med, argv[1]);
	/* now wait for the thread to exit */
	pthread_join(tid_sum, NULL);
	pthread_join(tid_avg, NULL);
	pthread_join(tid_min, NULL);
	pthread_join(tid_max, NULL);
	pthread_join(tid_med, NULL);

	printf("\nsum_value = %d\n", sum);
	printf("\nmean_value = %5.2f\n", avg);
	printf("n\nminimum_value = %d\n", min);
	printf("\nmaximum_value = %d\n", max);
	printf("\nmedian_value = %5.2f\n", med);
}

void* runner_sum(void *param) {
	int i, upper = atoi(param);
	sum = 0;
	printf("\nThread sum\n");
	for (i = 0; i <= size; i++)
		sum += num[i];

	pthread_exit(0);
}
void* runner_avg(void *param) {
	int i, upper = atoi(param);
	int ttl = 0;
	printf("Thread avg\n");
	for (i = 0; i <= size; i++)
		ttl += num[i];
	avg = ttl / (float) size;
	pthread_exit(0);
}
void* runner_max(void *param) {
	int i, upper = atoi(param);
	int temp = num[0];
	printf("\nThread max\n");
	for (i = 0; i < size; i++)
		if (temp < num[i])
			temp = num[i];
	max = temp;
	pthread_exit(0);
}
void* runner_min(void *param) {
	int i, upper = atoi(param);
	int temp = num[0];
	printf("\nThread min\n");
	for (i = 0; i < size; i++)
		if (temp > num[i])
			temp = num[i];
	min = temp;

	pthread_exit(0);
}

void* runner_med(void *param) {
	num_sort();
	printf("\nThread med\n");
	// if number of elements are even
	if (size % 2 == 0)
		med = (num[(size - 1) / 2] + num[size / 2]) / 2.0;
	// if number of elements are odd
	else
		med = num[size / 2];
	printf("\nmed=%5.2f\n", med);
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
