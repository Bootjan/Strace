#ifndef FT_STRACE_H
# define FT_STRACE_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdbool.h>
# include <string.h>
# include <signal.h>

# include <sys/types.h>
# include <sys/ptrace.h>
# include <sys/wait.h>
# include <sys/uio.h>
# include <sys/user.h>

# ifdef __linux__
#  include <linux/elf.h>
# endif

# ifdef __APPLE__
	typedef unsigned short	u_16int_t;
# endif

# define STDOUT_REDIRECTION ">temp/outfile.log"
# define STDERR_REDIRECTION "2>temp/outfile.log"
# define TRACEE_EXITED -1
# define TRACEE_RUNNING 0
# define SYSTEM_ERROR -2
# define SIGTRAP_STATUS 133

typedef long reg_t;

typedef struct {
	pid_t	pid;
	char*	cmd_path;
	char**	args;
	reg_t	syscall_nbr;
	reg_t	return_value;
	reg_t	args_regs[5];
}	strace_t;

char*		substr(char const *s, unsigned int start, size_t n);
char**		split_str(const char *s, char c);
const char*	find_path_envvar(char* const* envp);
char*		find_path_of_cmd(const char* cmd, const char** paths);
void		tracer(strace_t* strace);
void		quit_program(strace_t* strace, const char* message, u_int8_t exit_status);

// ||---- PRINTING SYSCALLS
const char*	get_syscall_name(u_int16_t syscall_number);
const char*	get_syscall_args_format(u_int16_t syscall_number);
void		print_syscall_with_args(strace_t* strace);
void		print_return_value(strace_t* strace);
const char* get_signal_name(u_int16_t signal_number);

#endif
