#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>

#define BUFFER_SIZE 10000

int main(int argc, char *argv[])
{
	int fd_1, fd_2;
	ssize_t ssize;
	size_t size;
	char infile[100], outfile[100];
	char buffer[BUFFER_SIZE];

	printf("Enter the filename to open for reading \n"); 
	scanf("%s", infile); 
	
	/*open inputfile in read mode */
	if ((fd_1 = open(infile, O_RDONLY)) == -1)
	{
		printf("Problem opening input file %s in read mode\n", infile);
		exit(0);
	};
	
	while ((ssize = read(fd_1, buffer, BUFFER_SIZE)) == BUFFER_SIZE)
	{

		if (ssize == -1)
		{ (void) fprintf(stderr, "Error reading file %s\n", infile);
			exit(EXIT_FAILURE);
		}
         printf("%s \n", buffer);
	}
	/*Close the input files */
	if (close(fd_1) != 0)
	{
		printf("Cannot close file %s \n", infile);
		exit(0);
	};
	return (0);
}