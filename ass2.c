#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

void main() {
            int i;
            for (i = 0; i < 4; i++)
                        fork();
            printf("\nhello my pid is %d and parent pid is %d\n",getpid(), getppid());
}