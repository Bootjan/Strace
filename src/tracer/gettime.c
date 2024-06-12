#include <sys/time.h>
#include <stddef.h>

double	gettime(void)
{
	struct timeval	tp;

	gettimeofday(&tp, NULL);
	return ((tp.tv_sec * 1000000) + (tp.tv_usec));
}
