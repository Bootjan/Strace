#include "ft_strace.h"

void	quit_program(strace_t* strace, const char* message, u_int8_t exit_status)
{
	if (exit_status == EXIT_FAILURE && message)
		fprintf(stderr, "%s\n", message);
	if (strace->cmd_path)
		free(strace->cmd_path);
	exit(exit_status);
}

void	free_string_array(char** array)
{
	for (int i = 0; array[i]; i++)
		free(array[i]);
	free(array);
}

char*	compute_path_to_command(strace_t* strace, const char* av, char* const* envp)
{
	const char*	path_envvar = find_path_envvar(envp);
	if (!path_envvar)
		quit_program(strace, "Error: couldn't find PATH environment variable", EXIT_FAILURE);
	char**		split_paths = split_str(&path_envvar[5], ':');
	if (!split_paths)
		quit_program(strace, "Error: failed to split PATH environment variable", EXIT_FAILURE);
	char*		cmd_path = find_path_of_cmd(av, (const char**)split_paths);
	free_string_array(split_paths);
	if (!cmd_path)
		quit_program(strace, "Error: failed to build path to command", EXIT_FAILURE);
	return (cmd_path);
}

void	tracee(strace_t* strace, char* const* av, char* const* envp)
{
	execve(strace->cmd_path, av, envp);
	if (strace->cmd_path)
		free(strace->cmd_path);
	exit(EXIT_FAILURE);
}

int	main(int ac, char* const* av, char* const* envp)
{
	strace_t	strace = (strace_t){ 0, NULL, _64BIT_PROC, 0, 0, {0, 0, 0, 0, 0, 0}, 0, NULL };

	if (ac < 2)
		quit_program(&strace, "Error: ft_strace expects at least 1 argument", EXIT_FAILURE);
	if (ac > 2 && strncmp(av[1], "-c", 3) == 0)
	{
		strace.flags |= PTRACE_C_FLAG;
		av = &(av[1]);
	}
	
	strace.cmd_path = compute_path_to_command(&strace, av[1], envp);

	if ((strace.pid = fork()) == -1)
		quit_program(&strace, "Error: fork command failed", EXIT_FAILURE);
	if (strace.pid > 0)
		tracer(&strace);
	else
		tracee(&strace, &(av[1]), envp);

	quit_program(&strace, NULL, EXIT_SUCCESS);
}
