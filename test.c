#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <stdio.h>
#include <signal.h>

// int	main(int ac, const char** av)
int	main(void)
{
	const char*	str = "Hallo\n";
	const char*	str2 = "Sletje\n";
	int fd = open("file1", O_RDONLY);
	if (fd == -1)
		printf("Failed to open file1\n");
	else
		close(fd);
	write(STDOUT_FILENO, str, strlen(str));
	kill(getpid(), SIGINT);
	write(STDOUT_FILENO, str2, strlen(str2));
	return (0);
}
