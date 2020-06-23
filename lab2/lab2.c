#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[]){
	int count=0; /* variable to hold the number of concurrent processes required by user */
	int pid ; /* variable to hold the process id returned by fork */
	int parray[count]; /* array holding the processes seq number along with their pid */ 
	printf("How many processes needed for the multitasking ?  \n");
		scanf("%d", &count); 
	printf("You requested %d processes\n", count); 
	for (int i = 0; i < count; i++){
		pid = fork();
		parray[i]= pid;
		printf("process %d has pid %d\n", i, pid);
	}
	return (0);
}