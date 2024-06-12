#ifndef FT_STRACE_H
# define FT_STRACE_H

// ||---- INCLUDES
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdbool.h>
# include <string.h>
# include <signal.h>
# include <stdio.h>

# include <sys/types.h>
# include <sys/ptrace.h>
# include <sys/wait.h>
# include <sys/uio.h>
# include <sys/user.h>
// # include <sys/siginfo.h>
# include <signal.h>

# ifdef __linux__
#  include <linux/elf.h>
# endif

# ifdef __APPLE__
	typedef unsigned short	u_16int_t;
# endif

// ||---- STATUS CODES
# define TRACEE_EXITED -1
# define TRACEE_RUNNING 0
# define SYSTEM_ERROR -2
# define TRACEE_RECEIVED_SIG 1
# define TRACER_RECEIVED_SIG 2
# define SIGTRAP_STATUS 133

// ||---- BIT FLAGS
# define PTRACE_C_FLAG 1
# define _64BIT_PROC 2
# define _32BIT_PROC 4

// ||---- PRINTING -c OPTION
# define MINUS_STRING_6 "------"
# define MINUS_STRING_10 "----------"
# define MINUS_STRING_20 "--------------------"

// ||---- TYPEDEFS
typedef long reg_t;
typedef long long t_time;

// ||---- STRUCTS
typedef struct syscall_list_s {
	long					syscall_nbr;
	int						calls;
	int						errors;
	double					interval;
	struct syscall_list_s*	next;
}	syslist_t;

typedef struct {
	pid_t			pid;
	char*			cmd_path;
	u_int8_t		flags;
	reg_t			syscall_nbr;
	reg_t			return_value;
	reg_t			args_regs[6];
	double			interval;
	syslist_t*		syscall_list;
}	strace_t;

struct i386_user_regs_struct {
	u_int32_t ebx;
	u_int32_t ecx;
	u_int32_t edx;
	u_int32_t esi;
	u_int32_t edi;
	u_int32_t ebp;
	u_int32_t eax;
	u_int32_t xds;
	u_int32_t xes;
	u_int32_t xfs;
	u_int32_t xgs;
	u_int32_t orig_eax;
	u_int32_t eip;
	u_int32_t xcs;
	u_int32_t eflags;
	u_int32_t esp;
	u_int32_t xss;
};

typedef union {
  struct user_regs_struct		x86_64_r;
  struct i386_user_regs_struct	i386_r;
}	regs_u;


// ||---- MAIN FUNCTIONS
void		tracer(strace_t* strace);
void		quit_program(strace_t* strace, const char* message, u_int8_t exit_status);


// ||---- PATH MANAGEMENT
char*		substr(char const *s, unsigned int start, size_t n);
char**		split_str(const char *s, char c);
const char*	find_path_envvar(char* const* envp);
char*		find_path_of_cmd(const char* cmd, const char** paths);


// ||---- SETTING REGISTERS
void		set_tracee_registers(strace_t* strace, struct iovec* data);
void		set_tracee_return_value(strace_t* strace, struct iovec* data);
void		set_64_32_bit_flag(strace_t* strace, size_t iov_len);


// ||---- HANDLE TRACEE
int			stop_tracee(strace_t* strace, int* status);
int			trace_syscall_and_wait(strace_t* strace, int* status);
int			check_if_tracee_exited(strace_t* strace, int status, bool first_of_cycle);
int			get_tracee_registers(pid_t pid, struct iovec* data);
int			retrieve_info_from_tracee(strace_t* strace, struct iovec* data, int* status, bool first_of_cycle);


// ||---- FETCHING SYSCALLS INFO
const char*	get_syscall_name(u_int16_t syscall_number, u_int8_t bit_flag);
const char*	get_syscall_args_format(u_int16_t syscall_number, u_int8_t bit_flag);
const char*	get_syscall_name_32bit(u_int16_t syscall_number);
const char*	get_syscall_args_format_32bit(u_int16_t syscall_number);
const char*	get_syscall_name_64bit(u_int16_t syscall_number);
const char*	get_syscall_args_format_64bit(u_int16_t syscall_number);


// ||---- HANDLING / PRINT TRACEE INFO
int			print_signal(strace_t* strace, siginfo_t* siginfo);
void		print_exit_status(strace_t* strace, int status);
int			handle_syscall_with_args(strace_t* strace);
void		handle_return_value(strace_t* strace);
const char* get_signal_name(u_int16_t signal_number);


// ||---- SYSCALL LIST MANIPULATION
void		print_syscall_list(strace_t* strace, u_int8_t bit_flag);
int			add_syscall_to_list(strace_t* strace);
void		update_syscall_list(strace_t* strace);
syslist_t*	sort_syscall_list(syslist_t* list);


// ||---- HANDLING SIGNALS
int			block_signals();
int			unblock_signals();
void		set_signal_handlers(pid_t tracee_pid);

// ||---- GET TIME
double		gettime(void);

#endif
