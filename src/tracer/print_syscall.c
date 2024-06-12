#include "ft_strace.h"

int	print_signal(strace_t* strace, siginfo_t* siginfo)
{
	if ((strace->flags & PTRACE_C_FLAG) > 0)
		return (0);
	if (!siginfo || siginfo->si_signo == SIGTRAP)
		return (0);
	fprintf(stderr, "+++ Tracee received signal: %s +++\n", get_signal_name(siginfo->si_signo));
	return (TRACEE_RECEIVED_SIG);
}

void	print_exit_status(strace_t* strace, int status)
{
	if ((strace->flags & PTRACE_C_FLAG) == 0)
		fprintf(stderr, "+++ exited with %i +++\n", WEXITSTATUS(status));
}

static void	print_syscall_args(strace_t* strace)
{
	const char*	syscall_args_format = get_syscall_args_format(strace->syscall_nbr, strace->flags);

	for (int i = 0; syscall_args_format[i]; i++)
	{
		if (i > 0)
			fprintf(stderr, ", ");
		if (syscall_args_format[i] == 'p')
			fprintf(stderr, "%p", (void *)strace->args_regs[i]);
		else
			fprintf(stderr, "%li", strace->args_regs[i]);
	}
}

static void	print_64bit_return_value(strace_t* strace)
{
	if (strace->syscall_nbr == 9)
		fprintf(stderr, ") = %p\n", (void *)strace->return_value);
	else if (strace->syscall_nbr == 60 || strace->syscall_nbr == 231)
		fprintf(stderr, ") = ?\n");
	else
		fprintf(stderr, ") = %li\n", strace->return_value);
}

static void	print_32bit_return_value(strace_t* strace)
{
	if (strace->syscall_nbr == 90)
		fprintf(stderr, ") = %p\n", (void *)strace->return_value);
	else if (strace->syscall_nbr == 1 || strace->syscall_nbr == 252)
		fprintf(stderr, ") = ?\n");
	else
		fprintf(stderr, ") = %li\n", strace->return_value);
}

void	handle_return_value(strace_t* strace)
{
	if ((strace->flags & PTRACE_C_FLAG) > 0)
	{
		update_syscall_list(strace);
		return;
	}	

	if ((strace->flags & _64BIT_PROC) > 0)
		print_64bit_return_value(strace);
	else
		print_32bit_return_value(strace);
}

int	handle_syscall_with_args(strace_t* strace)
{
	if ((strace->flags & PTRACE_C_FLAG) > 0)
	{
		if (add_syscall_to_list(strace) == -1)
			return (-1);
		return (0);
	}
	fprintf(stderr, "%s(", get_syscall_name(strace->syscall_nbr, strace->flags));
	print_syscall_args(strace);
	return (0);
}
