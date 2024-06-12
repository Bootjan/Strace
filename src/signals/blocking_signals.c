#include <signal.h>
#include <stddef.h>

int	block_signals()
{
	sigset_t	empty;
	sigemptyset(&empty);
	return (sigprocmask(SIG_SETMASK, &empty, NULL));
}

int	unblock_signals()
{
	int	signals[5] = { SIGHUP, SIGINT, SIGQUIT, SIGPIPE, SIGTERM };
	sigset_t	blocked;

	sigemptyset(&blocked);
	for (__uint8_t i = 0; i < 5; i++)
	{
		sigaddset(&blocked, signals[i]);

		if (sigprocmask(SIG_BLOCK, &blocked, NULL) == -1)
			return (-1);
	}
	return (0);
}
