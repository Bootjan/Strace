#include "ft_strace.h"
#include "ft_printf.h"

static void	print_syscall_args(strace_t* strace)
{
	const char*	syscall_args_format = get_syscall_args_format(strace->syscall_nbr);
	for (int i = 0; syscall_args_format[i]; i++)
	{
		if (i > 0)
			ft_printf(", ");
		if (syscall_args_format[i] == 'p')
			ft_printf("%p", (void *)strace->args_regs[i]);
		else
			ft_printf("%l", strace->args_regs[i]);
	}
}

void	print_return_value(strace_t* strace)
{
	if (strace->syscall_nbr == 9)
		ft_printf(") = %p\n", (void *)strace->return_value);
	else if (strace->return_value == -1)
		ft_printf(") = %c\n", '?');
	else
		ft_printf(") = %l\n", strace->return_value);
}

void	print_syscall_with_args(strace_t* strace)
{
	ft_printf("%s(", get_syscall_name(strace->syscall_nbr));
	print_syscall_args(strace);
}
