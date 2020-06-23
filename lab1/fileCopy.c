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
	if (argc !=3){
		printf("Enter the filename to open for reading \n"); 
		scanf("%s", infile); 
		printf("Enter the filename to open for writing \n");
		scanf("%s", outfile); 
	} else {
		strcpy(infile, argv[1]);
		printf("file copied from argv[1] is %s\n", infile);	
		strcpy(outfile, argv[2]);
		printf("\nfile copied from argv[2] is %s\n", outfile);
	}
	/*open inputfile in read mode */
	if ((fd_1 = open(infile, O_RDONLY)) == -1)
	{
		printf("Problem opening input file %s in read mode\n", infile);
		exit(0);
	};
	/*Open outputfile in write mode */
	if ((fd_2 = open(outfile, O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR)) == -1)
	{
		printf("Problem creating destination file %s \n", outfile);
		exit(0);
	};;

	while ((ssize = read(fd_1, buffer, BUFFER_SIZE)) == BUFFER_SIZE)
	{

		if (ssize == -1)
		{ (void) fprintf(stderr, "Error reading file %s\n", infile);
			exit(EXIT_FAILURE);
		}
		/*Write out the copy */
		if (write(fd_2, buffer, BUFFER_SIZE) != BUFFER_SIZE)
		{ (void) fprintf(stderr, " Error writing file %s\n", outfile);
			exit(EXIT_FAILURE);
		}
	}
	/*Close the input files */
	if (close(fd_1) != 0)
	{
		printf("Cannot close file %s \n", infile);
		exit(0);
	};
	/*Close the input files */
	if (close(fd_2) != 0)
	{
		printf("Cannot close file %s \n", outfile);
		exit(0);
	};
	/**/
	(void) printf("file %s copied to file %s\n", infile, outfile);
	return (0);
}