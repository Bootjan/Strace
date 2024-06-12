#include <signal.h>
#include <sys/types.h>
#include <stdio.h>
#include <stdbool.h>

static pid_t	tracee_pid_g = -1;
bool			received_ending_sig_g = false;

static void	signal_handler(int signum)
{
	received_ending_sig_g = true;
	if (tracee_pid_g <= 0)
		return;
	fprintf(stderr, "strace: Process %i detached\n", tracee_pid_g);
	kill(tracee_pid_g, signum);
}

void	set_signal_handlers(pid_t tracee_pid)
{
	tracee_pid_g = tracee_pid;

	signal(SIGQUIT, signal_handler);
	signal(SIGINT, signal_handler);
	signal(SIGTERM, signal_handler);
	signal(SIGTSTP, signal_handler);
}
