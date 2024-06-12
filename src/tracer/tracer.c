#include "ft_strace.h"

extern bool	received_ending_sig_g;

int	do_first_half_of_cycle(strace_t* strace, struct iovec* data, int* status)
{
	int	ret = retrieve_info_from_tracee(strace, data, status, true);
	if (received_ending_sig_g == true)
		return (TRACER_RECEIVED_SIG);
	if (ret == TRACEE_RECEIVED_SIG)
		return (TRACEE_RECEIVED_SIG);
	if (*status & (1 << 9) || ret != TRACEE_RUNNING)
		return (TRACEE_EXITED);

	set_64_32_bit_flag(strace, data->iov_len);
	set_tracee_registers(strace, data);
	handle_syscall_with_args(strace);
	
	return (TRACEE_RUNNING);
}

int	do_second_half_of_cycle(strace_t* strace, struct iovec* data, int* status)
{
	if (retrieve_info_from_tracee(strace, data, status, false) != TRACEE_RUNNING)
		return (TRACEE_EXITED);
	if (received_ending_sig_g == true)
		return (TRACEE_EXITED);

	set_64_32_bit_flag(strace, data->iov_len);
	set_tracee_return_value(strace, data);
	handle_return_value(strace);

	return (TRACEE_RUNNING);
}

int	do_syscall_cycle(strace_t* strace, struct iovec* data, int* status)
{
	int	ret = do_first_half_of_cycle(strace, data, status);
	if (ret == TRACER_RECEIVED_SIG)
		return (TRACER_RECEIVED_SIG);
	if (ret == TRACEE_EXITED)
		return (TRACEE_EXITED);
	if (ret == TRACEE_RECEIVED_SIG)
		return (TRACEE_RUNNING);
	
	if (do_second_half_of_cycle(strace, data, status) == TRACEE_EXITED)
		return (TRACEE_EXITED);

	return (TRACEE_RUNNING);
}

void	tracer(strace_t* strace)
{
	int		status;
	set_signal_handlers(strace->pid);
	if (stop_tracee(strace, &status) == -1)
		quit_program(strace, "Error: failed to stop tracee", EXIT_FAILURE);
	
	regs_u			regs;
	struct iovec	data = { &regs, sizeof(regs_u)};
	memset(&regs, 0, sizeof(regs_u));

	while (do_syscall_cycle(strace, &data, &status) == TRACEE_RUNNING)
		;

	if (received_ending_sig_g)
		quit_program(strace, "<detached ...>", EXIT_FAILURE);
	if (strace->flags & PTRACE_C_FLAG)
		print_syscall_list(strace, strace->flags);
	quit_program(strace, NULL, EXIT_SUCCESS);
}
