

#include <pthread.h>
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <math.h>


/* this data is shared by the thread(s) */
int  flag[2];
int turn ;

void* run_0(); /* The runner performed by the thread 0*/
void* run_1(); /* The runner performed by the thread 1*/


int main() {
	int ops_0, ops_1;
	pthread_t tid_0, tid_1; /* the int to identify each thread*/
	pthread_attr_t attr; /* set of attributes for the thread */
	flag[0]=0;
	flag[1]=0;
	turn=1;
	/* get the default attributes */
	pthread_attr_init(&attr);

	/* create the thread */
     printf("\n thread creation from parent pid=%d\n\n", getpid());
	ops_0 = 0;
	pthread_create(&tid_0, &attr, run_0, &ops_0);
  
	ops_1 =1;
	pthread_create(&tid_1, &attr, run_1, &ops_1);


	/* now wait for the thread to exit */
	pthread_join(tid_0, NULL);
	pthread_join(tid_1, NULL);
	return 1;
}

/* runner for the first thread */
void* run_0() {
	printf("\nin thread %d\n", getpid());
int task =1;

	
	while (task){
		flag[1]= 1;
		while(flag[1]){
			if (turn==0){
				flag[1]= 0;
				while(turn==0);
				flag[1]=1;
			}
		}}
	/* critical section */
		printf("\nCS");
	turn=0;
	flag[1]=0;
    printf("\n process id =%d", getpid());
    printf("\nEnd CS"); 
    pthread_exit(0);
	}

/* runner for the second thread */
void* run_1() {
	printf("\nin thread %d\n", getpid());
	int task =1;
	printf("in thread %d", getpid());
	while (task){
		flag[0]= 1;
		while(flag[1]){
			if (turn==1){
				flag[0]= 0;
				while(turn==1);
				flag[1]=1;
			}
		}} 
	/* critical section */
		printf("\nCS");
	turn=1;
	flag[0]=0;
    printf("\n process id =%d", getpid());
    printf("\nEnd CS");
    pthread_exit(0);
	}

 