#include "ft_strace.h"

void	quit_program(strace_t* strace, const char* message, u_int8_t exit_status)
{
	if (exit_status == EXIT_FAILURE)
		printf("Error: %s\n", message);
	if (strace->pid > 0)
		kill(strace->pid, SIGKILL);
	if (strace->cmd_path)
		free(strace->cmd_path);
	if (strace->args)
		free(strace->args);
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
		quit_program(strace, " couldn't find PATH environment variable", EXIT_FAILURE);
	char**		split_paths = split_str(path_envvar, ':');
	if (!split_paths)
		quit_program(strace, " failed to split PATH environment variable", EXIT_FAILURE);
	char*		cmd_path = find_path_of_cmd(av, (const char**)split_paths);
	free_string_array(split_paths);
	if (!cmd_path)
		quit_program(strace, " failed to build path to command", EXIT_FAILURE);
	return (cmd_path);
}

void	tracee(strace_t* strace, char* const* envp)
{
	execve(strace->cmd_path, strace->args, envp);
	if (strace->cmd_path)
		free(strace->cmd_path);
	if (strace->args)
		free(strace->args);
	exit(EXIT_FAILURE);
}

char**	compute_args_for_command(strace_t* strace, char* const* av)
{
	size_t	length = 0;

	for (; av[length]; length++)
		;
	char**	args = malloc((length + 3) * sizeof(char *));
	if (!args)
		quit_program(strace, " malloc failed", EXIT_FAILURE);
	for (length = 0; av[length]; length++)
		args[length] = av[length];

	args[length++] = STDOUT_REDIRECTION;
	args[length++] = STDERR_REDIRECTION;
	args[length] = NULL;
	return (args);
}

int	main(int ac, char* const* av, char* const* envp)
{
	strace_t	strace = (strace_t){ 0, NULL, NULL, 0, 0, {0, 0, 0, 0, 0} };

	if (ac < 2)
		quit_program(&strace, "ft_strace expects at least 1 argument", EXIT_FAILURE);
	strace.cmd_path = compute_path_to_command(&strace, av[1], envp);
	// strace.args = compute_args_for_command(&strace, &av[1]);

	if ((strace.pid = fork()) == -1)
		quit_program(&strace, " fork command failed", EXIT_FAILURE);
	if (strace.pid > 0)
		tracer(&strace);
	else
		tracee(&strace, envp);

	quit_program(&strace, "", EXIT_SUCCESS);
}
