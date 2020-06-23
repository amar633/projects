#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

FILE *inputfile, *outputfile;

#define BUFFER_SIZE 10

int main(int argc, char *argv[])
{
	int fd_1, fd_2;
	ssize_t ssize;
	size_t size;
	char buffer[BUFFER_SIZE];
	/*open inputfile in read mode */
	if ((fd_1 = open(argv[1], O_RDONLY)) == -1)
	{
		printf("Problem opening input file %s in read mode\n", argv[1]);
		exit(0);
	};
	/*Open outputfile in write mode */
	if ((fd_2 = open(argv[2], O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR)) == -1)
	{
		printf("Problem creating destination file %s \n", argv[2]);
		exit(0);
	};;

	while ((ssize = read(fd_1, buffer, BUFFER_SIZE)) == BUFFER_SIZE)
	{

		if (ssize == -1)
		{ (void) fprintf(stderr, "Error reading file %s\n", argv[1]);
			exit(EXIT_FAILURE);
		}
		/*Write out the copy */
		if (write(fd_2, buffer, BUFFER_SIZE) != BUFFER_SIZE)
		{ (void) fprintf(stderr, " Error writing file %s\n", argv[2]);
			exit(EXIT_FAILURE);
		}
	}
	/*Close the input files */
	if (close(fd_1) != 0)
	{
		printf("Cannot close file %s \n", argv[1]);
		exit(0);
	};
	/*Close the input files */
	if (close(fd_2) != 0)
	{
		printf("Cannot close file %s \n", argv[2]);
		exit(0);
	};
	/**/
	(void) printf("file %s copied to file %s\n", argv[1], argv[2]);
	return (0);
}