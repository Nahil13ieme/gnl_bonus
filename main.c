#include "get_next_line.h"
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

int main(void)
{
	int fd = open("test.txt", O_RDONLY);
	int fd2 = open("test2.txt", O_RDONLY);
	char *test;

	if (fd == -1) {
		perror("Error opening file");
		return (1);
	}
	if (fd2 == -1) {
		perror("Error opening file");
		return (1);
	}
	while ((test = get_next_line(fd)) != NULL) {
		printf("TEST LINE == --%s--\n", test);
		printf("================\n");
		free(test); // Free the allocated memory for the current line
	}
	printf("================\n");
	printf("================\n");
	printf("================\n");
	while ((test = get_next_line(fd2)) != NULL) {
		printf("TEST2 LINE == --%s--\n", test);
		printf("================\n");
		free(test); // Free the allocated memory for the current line
	}
	close(fd);
	return (0);
}
