#include <stdio.h> 
#include <sys/types.h> 
#include <unistd.h>  
int main() 
{ 
	int a=200;
if (fork() == 0) { 
    a = a + 5; 
    printf("\n\n%d, %d\n", a, &a); 
} 
else { 
    a = a - 5;
	printf("\n\n%d, %d\n", a, &a); 
} 
	return 0; 
} 
