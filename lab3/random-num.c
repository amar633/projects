// C program for generating a 
// random number in a given range. 
#include <stdio.h> 
#include <stdlib.h> 
#include <time.h> 

// Generates and prints 'size' random 
// numbers in range [lower, upper]. 
void printRandoms(int lower, int upper, 
							int size) 
{ 
	
	printf("\n\nEnter sample size: ");
		   scanf(" %d", &size);
	for (int i = 0; i < size; i++) { 
		int num = (rand() % 
		(upper - lower + 1)) + lower; 
		printf("%d --> %d  ",i,num); 
	} 
	printf("\n\n");
} 

// Driver code 
int main() 
{ 
	int lower = 0, upper = 100, size; 

	// Use current time as 
	// seed for random generator 
	srand(time(0)); 

	printRandoms(lower, upper, size); 

	return 0; 
} 
