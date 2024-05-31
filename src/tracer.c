#include "ft_strace.h"
#include "ft_printf.h"

int	stop_tracee(int pid, int* status)
{
	if (ptrace(PTRACE_SEIZE, pid, NULL, NULL) == -1)
		return (ft_printf("SEIZE: ptrace failed\n"), -1);
	if (ptrace(PTRACE_INTERRUPT, pid, NULL, NULL) == -1)
		return (ft_printf("INTERRUPT: ptrace failed\n"), -1);
	if (waitpid(pid, status, 0) == -1)
		return (ft_printf("Waitpid failed\n"), -1);
	if (ptrace(PTRACE_SETOPTIONS, pid, NULL, PTRACE_O_TRACESYSGOOD) == -1)
		return (ft_printf("SETOPTIONS failed\n"), -1);
	return 0;
}


int	trace_syscall_and_wait(pid_t pid, int* status)
{
	if (ptrace(PTRACE_SYSCALL, pid, NULL, NULL) == -1)
		return (ft_printf("SYSCALL: ptrace failed\n"), -1);
	if (waitpid(pid, status, 0) == -1)
		return (ft_printf("WAITPID: ptrace failed\n"), -1);
	return 0;
}

int	get_tracee_registers(pid_t pid, struct iovec* data)
{
	if (ptrace(PTRACE_GETREGSET, pid, NT_PRSTATUS, data) == -1)
		return (ft_printf("GETREGSET had an error\n"), -1);
	return 0;
}

void	set_tracee_registers(strace_t* strace, struct user_regs_struct* regs)
{
	strace->syscall_nbr = regs->orig_rax;
	strace->args_regs[0] = regs->rdi;
	strace->args_regs[1] = regs->rsi;
	strace->args_regs[2] = regs->rdx;
	strace->args_regs[3] = regs->r10;
	strace->args_regs[4] = regs->r9;
}

void	print_signal(strace_t* strace)
{
	ft_printf("+++ %s by %s +++\n", strsignal(strace->args_regs[1]), get_signal_name(strace->args_regs[1]));
}

void	print_exit_status(int status)
{
	ft_printf("+++ exited with %i +++\n", WEXITSTATUS(status));
}

int	check_if_tracee_exited(strace_t* strace, int status)
{
	if (WEXITSTATUS(status) != SIGTRAP_STATUS)
	{
		strace->return_value = -1;
		print_return_value(strace);
		print_signal(strace);
		return (TRACEE_EXITED);
	}

	if (WIFEXITED(status))
	{
		strace->return_value = -1;
		print_return_value(strace);
		print_exit_status(status);
		return (TRACEE_EXITED);
	}
	
	return (TRACEE_RUNNING);
}

int	handle_syscall(strace_t* strace, int* status)
{
	struct user_regs_struct regs;
	struct iovec			data = { &regs, sizeof(struct user_regs_struct)};
	memset(&regs, 0, sizeof(struct user_regs_struct));

	siginfo_t				siginfo;
	memset(&siginfo, 0, sizeof(siginfo_t));

	if (check_if_tracee_exited(strace, *status) == TRACEE_EXITED)
		return (TRACEE_EXITED);

	if (get_tracee_registers(strace->pid, &data) == -1)
		return SYSTEM_ERROR; // handle error
	set_tracee_registers(strace, &regs);
	print_syscall_with_args(strace);

	if (trace_syscall_and_wait(strace->pid, status) == -1)
		return SYSTEM_ERROR; // handle error

	if (check_if_tracee_exited(strace, *status) == TRACEE_EXITED)
		return (TRACEE_EXITED);

	if (ptrace(PTRACE_GETSIGINFO, strace->pid, NULL, &siginfo) == -1)
		ft_printf("SETSIGINFO had an error\n");

	if (get_tracee_registers(strace->pid, &data) == -1)
		return SYSTEM_ERROR; // handle error
	strace->return_value = regs.rax;

	return (print_return_value(strace), TRACEE_RUNNING);
}

void	handle_signal(strace_t strace, int* status)
{
	(void)strace;
	(void)status;
	ft_printf("Tracee received a signal\n");
}

void	tracer(strace_t* strace)
{
	int		status;
	if (stop_tracee(strace->pid, &status) == -1)
		quit_program(strace, " failed to stop tracee", EXIT_FAILURE);
	
	siginfo_t				siginfo;
	memset(&siginfo, 0, sizeof(siginfo_t));

	while (true)
	{
		if (trace_syscall_and_wait(strace->pid, &status) == -1)
			break ;

		if (ptrace(PTRACE_GETSIGINFO, strace->pid, NULL, &siginfo) == -1)
			ft_printf("SETSIGINFO had an error\n");

		if (handle_syscall(strace, &status) == TRACEE_EXITED)
			break ;
	}
	quit_program(strace, "", EXIT_SUCCESS);
}
