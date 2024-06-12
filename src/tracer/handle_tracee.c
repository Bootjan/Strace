#include "ft_strace.h"

int	wait_for_tracee(strace_t* strace, int* status)
{
	double	start, stop;

	if (block_signals() == -1)
		return (-1);
	start = gettime();

	if (waitpid(strace->pid, status, 0) == -1)
		return (fprintf(stderr, "WAITPID: ptrace failed\n"), -1);

	stop = gettime();
	if (unblock_signals() == -1)
		return (-1);
	
	strace->interval = (stop - start) / 1000000;
	return (0);
}

int	stop_tracee(strace_t* strace, int* status)
{
	if (ptrace(PTRACE_SEIZE, strace->pid, NULL, NULL) == -1)
		return (fprintf(stderr, "SEIZE: ptrace failed\n"), -1);
	if (ptrace(PTRACE_INTERRUPT, strace->pid, NULL, NULL) == -1)
		return (fprintf(stderr, "INTERRUPT: ptrace failed\n"), -1);
	if (wait_for_tracee(strace, status) == -1)
		return (fprintf(stderr, "Waitpid failed\n"), -1);
	if (ptrace(PTRACE_SETOPTIONS, strace->pid, NULL, PTRACE_O_TRACESYSGOOD | PTRACE_O_TRACECLONE) == -1)
		return (fprintf(stderr, "SETOPTIONS failed\n"), -1);
	return 0;
}

int	trace_syscall_and_wait(strace_t* strace, int* status)
{
	if (ptrace(PTRACE_SYSCALL, strace->pid, NULL, NULL) == -1)
		return (fprintf(stderr, "SYSCALL: ptrace failed\n"), SYSTEM_ERROR);

	if (wait_for_tracee(strace, status) == -1)
		return (SYSTEM_ERROR);
	

	return (TRACEE_RUNNING);
}

int	check_if_tracee_exited(strace_t* strace, int status, bool first_of_cycle)
{
	if (!WIFEXITED(status))
		return (TRACEE_RUNNING);

	strace->return_value = -1;
	strace->interval = 0;
	if (!first_of_cycle)
		handle_return_value(strace);
	print_exit_status(strace, status);
	return (TRACEE_EXITED);
}

int	get_tracee_registers(pid_t pid, struct iovec* data)
{
	if (ptrace(PTRACE_GETREGSET, pid, NT_PRSTATUS, data) == -1)
		return (fprintf(stderr, "GETREGSET had an error\n"), -1);
	return 0;
}

int	retrieve_info_from_tracee(strace_t* strace, struct iovec* data, int* status, bool first_of_cycle)
{
	siginfo_t	siginfo;
	memset(&siginfo, 0, sizeof(siginfo_t));

	if (trace_syscall_and_wait(strace, status) != TRACEE_RUNNING)
		return (TRACEE_EXITED);
	
	if (check_if_tracee_exited(strace, *status, first_of_cycle) != TRACEE_RUNNING)
		return (TRACEE_EXITED);

	if (get_tracee_registers(strace->pid, data) == -1)
		return (SYSTEM_ERROR);

	if (ptrace(PTRACE_GETSIGINFO, strace->pid, NULL, &siginfo) == -1)
		return (SYSTEM_ERROR);
	
	if (print_signal(strace, &siginfo) == TRACEE_RECEIVED_SIG)
		return (TRACEE_RECEIVED_SIG);
	
	return (TRACEE_RUNNING);
}
