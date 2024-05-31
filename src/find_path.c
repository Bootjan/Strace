#include "ft_strace.h"

const char*	find_path_envvar(char* const* envp)
{
	for (int i = 0; envp[i]; i++)
		if (strncmp(envp[i], "PATH=", 5) == 0)
			return envp[i];
	return (NULL);
}

static char* compute_cmd_path(const char* cmd, const char* path)
{
	int 	cmd_size = strlen(cmd);
	int		path_size = strlen(path);

	char*	cmd_path = malloc(cmd_size + path_size + 2);
	if (!cmd_path)
		return (NULL);

	strncpy(cmd_path, cmd, cmd_size + 1);
	strncat(cmd_path, path, path_size);
	return (cmd_path);
}

char*	find_path_of_cmd(const char* cmd, const char** paths)
{
	if (access(cmd, X_OK) != -1)
		return (strdup(cmd));
	for (int idx = 0; paths[idx]; idx++)
	{
		char*	cmd_path = compute_cmd_path(cmd, paths[idx]);
		if (!cmd_path)
			return (NULL);
		if (access(cmd_path, X_OK) != -1)
			return (cmd_path);
		free(cmd_path);
	}
	return (NULL);
}
