#include <stdio.h> 
#include <sys/types.h> 
#include <unistd.h> 

#define N 2 
int main() 
{ 
	for (int i = 0; i < N; i++) {
	fork(); 
 	printf("\nHello num: %d\n",i);
	}
	return 0; 
} 
