

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

int main() {
	int ops_0=fork();
	int ops_1 =fork();
    run_0(0);
	run_0(1);
	return 1;
}

/* runner for the first thread */
void* run_0(int i) {
int task =1;	
	while (task){
		flag[(i+1)%2]= 1;
		while(flag[(i+1)%2]){
			if (turn==0){
				flag[(i+1)%2]= 0;
				while(turn==i);
				flag[(i+1)%2]=1;
			}
		}}
	/* critical section */
	printf("\nCS");
	turn=0;
	flag[1]=0;
    printf("\n process id =%d", getpid());
    printf("\nEnd CS"); 
	}

