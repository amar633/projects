#include <pthread.h>
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>


#define NUM_THREADS 5
#define MAX_DATA 100
void *runner(void *param); /* the thread */


int main(int argc, char *argv[]) {
	int i, scope, sum=0;
	int DATA[MAX_DATA];
	if (argc < 2){
		printf("\n\nNot enough data to run the program!\n");
		exit(0);
	}
	for (int k=0; k < argc; k++){
		DATA[k] = atoi(argv[k+1]);
	}
	pthread_t tid[NUM_THREADS];
	pthread_attr_t attr;
	/*get the default attributes */
	pthread_attr_init(&attr);
	/*first inquire on the current scope */
	if (pthread_attr_getscope(&attr, &scope) != 0)
		fprintf(stderr, "Unable to get scheduling scope\n");
	else
	{
		if (scope == PTHREAD_SCOPE_PROCESS)
			printf("PTHREAD_SCOPE_PROCESS");
		else if (scope == PTHREAD_SCOPE_SYSTEM)
			printf("PTHREAD_SCOPE_SYSTEM");
		else
			fprintf(stderr, "Illegal scope value.\n");
	}
	/*set the scheduling algorithm to PCS or SCS */
	pthread_attr_setscope(&attr, PTHREAD_SCOPE_SYSTEM);
	/*create the threads */
	for (i = 0; i < NUM_THREADS; i++)
		pthread_create(&tid[i], &attr, runner, NULL);
	/*now join on each thread */
	for (i = 0; i < NUM_THREADS; i++)
		pthread_join(tid[i], NULL);
}
/*Each thread will begin control in this function */
void *runner(void *param)
	{   int sum =0;
	 printf("mAX_DATA =%d\n", MAX_DATA);
	    int DATA[MAX_DATA];
	    int m = atoi(param);
		for (int k=0; k <= m; k++){
			sum += DATA[k];
		}
	printf("\n\n sum= %d\n", sum);
		pthread_exit(0);
	}