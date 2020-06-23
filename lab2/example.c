#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>


int main()
{
    int count=0; /* variable to hold the number of concurrent processes required by user */
    int pid, ppid ; /* variables to hold the process id rfor both child and parent processes */
    printf("How many processes needed for the multitasking ?  \n");
    scanf("%d", &count);
    for(int i=0; i<count; i++) // loop will run n times (n=5)
    {
        if(fork() == 0)
        {
            printf("\n[Hello I am  child %d of parent %d and my pid is %d \n",i, getppid(),getpid());
            exit(0);
        }
    }
    /* The parent process has to wait a number of times exactly
    equal to the number of children it has spawn to perform enough wait for each child to finish executing.
    However, we have no clue for which specific child a current wait applies.
    This is left to the discretion of the OS. We can pnly provide enough wait to satisfy the requirement o lab2. */
    for(int i=0; i<count; i++) {
		/* print to make sure the wait is for the parent process. Commented out after debug done */
        printf("\n process %d is waiting", getpid());
        wait(NULL);
    }

}