#include "ft_strace.h"

const char* get_syscall_name(u_int16_t syscall_number, u_int8_t bit_flag)
{
	if ((bit_flag & _32BIT_PROC) > 0)
		return (get_syscall_name_32bit(syscall_number));
	return (get_syscall_name_64bit(syscall_number));
}

const char* get_syscall_args_format(u_int16_t syscall_number, u_int8_t bit_flag)
{
	if ((bit_flag & _32BIT_PROC) > 0)
		return (get_syscall_args_format_32bit(syscall_number));
	return (get_syscall_args_format_64bit(syscall_number));
}
