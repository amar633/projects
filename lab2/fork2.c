//fork2.c

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>

int main()
{
    int pid;
    /* fork another process */
    pid = fork();
    if (pid < 0) {
        /* error occurred */
        printf("Fork Failed\n");
        exit(-1);
    }
    else if (pid == 0) {
        /* child process */
        execlp("/bin/more", "more", "lab2txt",NULL);
    }
    else {
        /* parent process */
        /* parent will wait for the child to complete */
        wait(NULL);

        printf("Child Complete\n");
        exit(0);
    }
    return 0;
}