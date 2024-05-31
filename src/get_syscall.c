const static char* syscalls_g[] = {
	"read", "ipi",
	"write", "ipi",
	"open", "pii",
	"close", "i",
	"stat", "pp",
	"fstat", "ip",
	"lstat", "pp",
	"poll", "pii",
	"lseek", "iii",
	"mmap", "piiip",
	"mprotect", "pii",
	"munmap", "pi",
	"brk", "i",
	"rt_sigaction", "ippi",
	"rt_sigprocmask", "ippi",
	"rt_sigreturn", "",
	"ioctl", "iii",
	"pread64", "ipii",
	"pwrite64", "ipii",
	"readv", "ipi",
	"writev", "ipi",
	"access", "pi",
	"pipe", "p",
	"select", "ipppp",
	"sched_yield", "",
	"mremap", "iiiii",
	"msync", "iii",
	"mincore", "iip",
	"madvise", "iii",
	"shmget", "iii",
	"shmat", "ipi",
	"shmctl", "iip",
	"dup", "i",
	"dup2", "ii",
	"pause", "",
	"nanosleep", "pp",
	"getitimer", "ip",
	"alarm", "i",
	"setitimer", "ipp",
	"getpid", "",
	"sendfile", "iipi",
	"socket", "iii",
	"connect", "ipi",
	"accept", "ipp",
	"sendto", "ipiipi",
	"recvfrom", "ipiipp",
	"sendmsg", "ipi",
	"recvmsg", "ipi",
	"shutdown", "ii",
	"bind", "ipi",
	"listen", "ii",
	"getsockname", "ipp",
	"getpeername", "ipp",
	"socketpair", "iiip",
	"setsockopt", "iiipi",
	"getsockopt", "iiipp",
	"clone", "iippi",
	"fork", "",
	"vfork", "",
	"execve", "ppp",
	"exit", "i",
	"wait4", "ipip",
	"kill", "ii",
	"uname", "p",
	"semget", "iii",
	"semop", "ipi",
	"semctl", "iiii",
	"shmdt", "p",
	"msgget", "ii",
	"msgsnd", "ipii",
	"msgrcv", "ipiii",
	"msgctl", "iip",
	"fcntl", "iii",
	"flock", "ii",
	"fsync", "i",
	"fdatasync", "i",
	"truncate", "pi",
	"ftruncate", "ii",
	"getdents", "ipi",
	"getcwd", "pi",
	"chdir", "p",
	"fchdir", "i",
	"rename", "pp",
	"mkdir", "pi",
	"rmdir", "p",
	"creat", "pi",
	"link", "pp",
	"unlink", "p",
	"symlink", "pp",
	"readlink", "ppi",
	"chmod", "pi",
	"fchmod", "ii",
	"chown", "pii",
	"fchown", "iii",
	"lchown", "pii",
	"umask", "i",
	"gettimeofday", "pp",
	"getrlimit", "ip",
	"getrusage", "ip",
	"sysinfo", "p",
	"times", "p",
	"ptrace", "iiii",
	"getuid", "",
	"syslog", "ipi",
	"getgid", "",
	"setuid", "i",
	"setgid", "i",
	"geteuid", "",
	"getegid", "",
	"setpgid", "ii",
	"getppid", "",
	"getpgrp", "",
	"setsid", "",
	"setreuid", "ii",
	"setregid", "ii",
	"getgroups", "ip",
	"setgroups", "ip",
	"setresuid", "iii",
	"getresuid", "ppp",
	"setresgid", "iii",
	"getresgid", "ppp",
	"getpgid", "i",
	"setfsuid", "i",
	"setfsgid", "i",
	"getsid", "i",
	"capget", "ii",
	"capset", "ii",
	"rt_sigpending", "pi",
	"rt_sigtimedwait", "pppi",
	"rt_sigqueueinfo", "iip",
	"rt_sigsuspend", "pi",
	"sigaltstack", "pp",
	"utime", "pp",
	"mknod", "pii",
	"uselib", "p",
	"personality", "i",
	"ustat", "ip",
	"statfs", "pp",
	"fstatfs", "ip",
	"sysfs", "iii",
	"getpriority", "ii",
	"setpriority", "iii",
	"sched_setparam", "ip",
	"sched_getparam", "ip",
	"sched_setscheduler", "iip",
	"sched_getscheduler", "i",
	"sched_get_priority_max", "i",
	"sched_get_priority_min", "i",
	"sched_rr_get_interval", "ip",
	"mlock", "ii",
	"munlock", "ii",
	"mlockall", "i",
	"munlockall", "",
	"vhangup", "",
	"modify_ldt", "",
	"pivot_root", "pp",
	"_sysctl", "",
	"prctl", "iiiii",
	"arch_prctl", "ip",
	"adjtimex", "p",
	"setrlimit", "ip",
	"chroot", "p",
	"sync", "",
	"acct", "p",
	"settimeofday", "pp",
	"mount", "pppip",
	"umount2", "",
	"swapon", "pi",
	"swapoff", "p",
	"reboot", "iiip",
	"sethostname", "pi",
	"setdomainname", "pi",
	"iopl", "",
	"ioperm", "iii",
	"create_module", "",
	"init_module", "pip",
	"delete_module", "pi",
	"get_kernel_syms", "",
	"query_module", "",
	"quotactl", "ipip",
	"nfsservctl", "",
	"getpmsg", "",
	"putpmsg", "",
	"afs_syscall", "",
	"tuxcall", "",
	"security", "",
	"gettid", "",
	"readahead", "iii",
	"setxattr", "pppii",
	"lsetxattr", "pppii",
	"fsetxattr", "ippii",
	"getxattr", "pppi",
	"lgetxattr", "pppi",
	"fgetxattr", "ippi",
	"listxattr", "ppi",
	"llistxattr", "ppi",
	"flistxattr", "ipi",
	"removexattr", "pp",
	"lremovexattr", "pp",
	"fremovexattr", "ip",
	"tkill", "ii",
	"time", "p",
	"futex", "piippi",
	"sched_setaffinity", "iip",
	"sched_getaffinity", "iip",
	"set_thread_area", "",
	"io_setup", "ip",
	"io_destroy", "i",
	"io_getevents", "iiipp",
	"io_submit", "iip",
	"io_cancel", "ipp",
	"get_thread_area", "",
	"lookup_dcookie", "ipi",
	"epoll_create", "i",
	"epoll_ctl_old", "",
	"epoll_wait_old", "",
	"remap_file_pages", "iiiii",
	"getdents64", "ipi",
	"set_tid_address", "p",
	"restart_syscall", "",
	"semtimedop", "ipip",
	"fadvise64", "iiii",
	"timer_create", "ipp",
	"timer_settime", "iipp",
	"timer_gettime", "ip",
	"timer_getoverrun", "i",
	"timer_delete", "i",
	"clock_settime", "ip",
	"clock_gettime", "ip",
	"clock_getres", "ip",
	"clock_nanosleep", "iipp",
	"exit_group", "i",
	"epoll_wait", "ipii",
	"epoll_ctl", "iiip",
	"tgkill", "iii",
	"utimes", "pp",
	"vserver", "",
	"mbind", "iiipii",
	"set_mempolicy", "ipi",
	"get_mempolicy", "ppiii",
	"mq_open", "piip",
	"mq_unlink", "p",
	"mq_timedsend", "ipiip",
	"mq_timedreceive", "ipipp",
	"mq_notify", "ip",
	"mq_getsetattr", "ipp",
	"kexec_load", "iipi",
	"waitid", "iipip",
	"add_key", "pppii",
	"request_key", "pppi",
	"keyctl", "iiiii",
	"ioprio_set", "iii",
	"ioprio_get", "ii",
	"inotify_init", "",
	"inotify_add_watch", "ipi",
	"inotify_rm_watch", "ii",
	"migrate_pages", "iipp",
	"openat", "ipii",
	"mkdirat", "ipi",
	"mknodat", "ipii",
	"fchownat", "ipiii",
	"futimesat", "ipp",
	"newfstatat", "ippi",
	"unlinkat", "ipi",
	"renameat", "ipip",
	"linkat", "ipipi",
	"symlinkat", "pip",
	"readlinkat", "ippi",
	"fchmodat", "ipi",
	"faccessat", "ipi",
	"pselect6", "ippppp",
	"ppoll", "pippi",
	"unshare", "i",
	"set_robust_list", "pi",
	"get_robust_list", "ipp",
	"splice", "ipipii",
	"tee", "iiii",
	"sync_file_range", "iiii",
	"vmsplice", "ipii",
	"move_pages", "iipppi",
	"utimensat", "ippi",
	"epoll_pwait", "ipiipi",
	"signalfd", "ipi",
	"timerfd_create", "ii",
	"eventfd", "i",
	"fallocate", "iiii",
	"timerfd_settime", "iipp",
	"timerfd_gettime", "ip",
	"accept4", "ippi",
	"signalfd4", "ipii",
	"eventfd2", "ii",
	"epoll_create1", "i",
	"dup3", "iii",
	"pipe2", "pi",
	"inotify_init1", "i",
	"preadv", "ipiii",
	"pwritev", "ipiii",
	"rt_tgsigqueueinfo", "iiip",
	"perf_event_open", "piiii",
	"recvmmsg", "ipiip",
	"fanotify_init", "ii",
	"fanotify_mark", "iiiip",
	"prlimit64", "iipp",
	"name_to_handle_at", "ipppi",
	"open_by_handle_at", "ipi",
	"clock_adjtime", "ip",
	"syncfs", "i",
	"sendmmsg", "ipii",
	"setns", "ii",
	"getcpu", "ppp",
	"process_vm_readv", "ipipii",
	"process_vm_writev", "ipipii",
	"kcmp", "iiiii",
	"finit_module", "ipi",
	"sched_setattr", "ipi",
	"sched_getattr", "ipii",
	"renameat2", "ipipi",
	"seccomp", "iip",
	"getrandom", "pii",
	"memfd_create", "pi",
	"kexec_file_load", "iiipi",
	"bpf", "ipi",
	"execveat", "ipppi",
	"userfaultfd", "i",
	"membarrier", "ii",
	"mlock2", "iii",
	"copy_file_range", "ipipii",
	"preadv2", "ipiiii",
	"pwritev2", "ipiiii",
	"pkey_mprotect", "piii",
	"pkey_alloc", "ii",
	"pkey_free", "i",
	"statx", "ipiip",
	"io_pgetevents", "iiipp",
	"rseq", "pii",
	// "pidfd_send_signal",
	// "io_uring_setup",
	// "io_uring_enter",
	// "io_uring_register",
	// "open_tree",
	// "move_mount",
	// "fsopen",
	// "fsconfig",
	// "fsmount",
	// "fspick",
	// "pidfd_open",
	// "clone3",
	// "close_range",
	// "openat2",
	// "pidfd_getfd",
	// "faccessat2",
	// "process_madvise",
	// "epoll_pwait2",
	// "mount_setattr",
	// "quotactl_fd",
	// "landlock_create_ruleset",
	// "landlock_add_rule",
	// "landlock_restrict_self",
	// "memfd_secret",
	// "process_mrelease",
	// "futex_waitv",
	// "set_mempolicy_home_node",
	// "cachestat",
	// "fchmodat2",
	// "map_shadow_stack",
	// "futex_wake",
	// "futex_wait",
	// "futex_requeu"
};

#include "ft_strace.h"

const char*	get_syscall_name(u_int16_t syscall_number)
{
	return ( syscalls_g[syscall_number * 2]);
}

const char*	get_syscall_args_format(u_int16_t syscall_number)
{
	return (syscalls_g[syscall_number * 2 + 1]);
}