#include "ft_strace.h"

const char* get_signal_name(u_int16_t signal_number)
{
	switch (signal_number)
	{
		case SIGHUP:
			return ("SIGHUP");
		case SIGINT:
			return ("SIGINT");
		case SIGQUIT:
			return ("SIGQUIT");
		case SIGILL:
			return ("SIGILL");
		case SIGTRAP:
			return ("SIGTRAP");
		case SIGABRT:
			return ("SIGABRT");
		case SIGBUS:
			return ("SIGBUS");
		case SIGFPE:
			return ("SIGFPE");
		case SIGKILL:
			return ("SIGKILL");
		case SIGUSR1:
			return ("SIGUSR1");
		case SIGSEGV:
			return ("SIGSEGV");
		case SIGUSR2:
			return ("SIGUSR2");
		case SIGPIPE:
			return ("SIGPIPE");
		case SIGALRM:
			return ("SIGALRM");
		case SIGTERM:
			return ("SIGTERM");
		case SIGSTKFLT:
			return ("SIGSTKFLT");
		case SIGCHLD:
			return ("SIGCHLD");
		case SIGCONT:
			return ("SIGCONT");
		case SIGSTOP:
			return ("SIGSTOP");
		case SIGTSTP:
			return ("SIGTSTP");
		case SIGTTIN:
			return ("SIGTTIN");
		case SIGTTOU:
			return ("SIGTTOU");
		case SIGURG:
			return ("SIGURG");
		case SIGXCPU:
			return ("SIGXCPU");
		case SIGXFSZ:
			return ("SIGXFSZ");
		case SIGVTALRM:
			return ("SIGVTALRM");
		case SIGPROF:
			return ("SIGPROF");
		case SIGWINCH:
			return ("SIGWINCH");
		case SIGIO:
			return ("SIGIO");
		case SIGPWR:
			return ("SIGPWR");
		case SIGSYS:
			return ("SIGSYS");
		default:
			return ("UNKNOWN SIGNAL");
	}
}
