#include <stdio.h> 
#include <sys/types.h> 
#include <unistd.h> 

void forkexample() 
{ 
	int x = 1; 

	if (fork() == 0) 
		printf("C\nhild has x = %d\n", ++x); 
	else
		printf("\nParent has x = %d\n", --x); 
} 
int main() 
{ 
	forkexample(); 
	return 0; 
} 
