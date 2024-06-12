#include "ft_strace.h"

static void	set_32bit_registers(strace_t* strace, struct iovec* data)
{
	struct i386_user_regs_struct* regs = data->iov_base;
	strace->syscall_nbr = regs->orig_eax;
	strace->args_regs[0] = regs->ebx;
	strace->args_regs[1] = regs->ecx;
	strace->args_regs[2] = regs->edx;
	strace->args_regs[3] = regs->esi;
	strace->args_regs[4] = regs->edi;
}

static void	set_64bit_registers(strace_t* strace, struct iovec* data)
{
	struct user_regs_struct* regs = data->iov_base;
	strace->syscall_nbr = regs->orig_rax;
	strace->args_regs[0] = regs->rdi;
	strace->args_regs[1] = regs->rsi;
	strace->args_regs[2] = regs->rdx;
	strace->args_regs[3] = regs->r10;
	strace->args_regs[4] = regs->r9;
	strace->args_regs[5] = regs->r8;
}

void	set_tracee_registers(strace_t* strace, struct iovec* data)
{
	if ((strace->flags & _32BIT_PROC) > 0)
		set_32bit_registers(strace, data);
	else
		set_64bit_registers(strace, data);
}

void	set_tracee_return_value(strace_t* strace, struct iovec* data)
{
	if ((strace->flags & _32BIT_PROC) > 0)
	{
		struct i386_user_regs_struct* regs = data->iov_base;
		if ((int)(regs->eax) > -24 && (int)(regs->eax) < 0)
			strace->return_value = (int)(regs->eax);
		else
			strace->return_value = regs->eax;
	}
	else
	{
		struct user_regs_struct* regs = data->iov_base;
		strace->return_value = regs->rax;
	}
}

static void	print_switching_statement(u_int8_t bit_flag)
{
	fprintf(stderr, "\n++++++++++++++++++++++++++++++\n");
	if ((bit_flag & _32BIT_PROC) > 0)
		fprintf(stderr, "+ Switched to 32 bit process +\n");
	else
		fprintf(stderr, "+ Switched to 64 bit process +\n");
	fprintf(stderr, "++++++++++++++++++++++++++++++\n\n");
}

void	set_64_32_bit_flag(strace_t* strace, size_t iov_len)
{
	u_int8_t	old_flag = strace->flags;

	if (iov_len == sizeof(struct i386_user_regs_struct))
		strace->flags = (_32BIT_PROC | (strace->flags & PTRACE_C_FLAG));
	else
		strace->flags = (_64BIT_PROC | (strace->flags & PTRACE_C_FLAG));

	if (old_flag != strace->flags && (strace->flags & PTRACE_C_FLAG) > 0)
	{
		print_syscall_list(strace, old_flag);
		print_switching_statement(strace->flags);
		strace->syscall_list = NULL;
	}
}
