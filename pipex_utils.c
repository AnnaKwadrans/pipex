#include "pipex.h"

void    print_array(char **env)
{
    int i;

    i = 0;
    while (env[i])
    {
        ft_printf("%s\n", env[i]);
        i++;
    }
	free(env);
}

void    free_array(char **str)
{
    int i;

    i = 0;
    while (str[i])
    {
		free(str[i]);
        i++;
    }
	free(str);
}


char	**parse_commands(char *str)
{
	char	**cmds;

	cmds = ft_split(str, ' ');
	return (cmds);
}

char	**parse_path_var(char **env)
{
	int		i;
	char	**paths;

	i = 0;
	while (env[i])
	{
		if (strncmp(env[i], "PATH=", 5) == 0 && env[i][5])
		{
			paths = ft_split(env[i] + 5, ':');
			if (paths)
				return (paths);
		}
		i++;
	}
	return (NULL);
}

char	*get_path(char *cmd, char **envp)
{
	char	**paths_array;
	int		i;
	char	*aux;
	char	*path;

	paths_array = parse_path_var(envp);
	if (paths_array == NULL)
		return (NULL);
	i = 0;
	while (paths_array[i] != NULL)
	{
		//ft_printf("%s\n", paths_array[i]);
		aux = ft_strjoin(paths_array[i], "/");
		//ft_printf("chk %d: %s\n", i, aux);
		path = ft_strjoin(aux, cmd);
		//ft_printf("chk %d: %s\n", i, path);
		free(aux);
		if (access(path, F_OK) == 0)
		{
			free_array(paths_array);
			return (path);
		}
		free(path);
		i++;
	}
	free_array(paths_array);
	return (NULL);
}

void	exec_cmd(char *cmd, char **env)
{
	char	**cmds_array;
	char	*path;

	cmds_array = ft_split(cmd, ' ');
	path = get_path(cmds_array[0], env);
	execve(path, cmds_array, env);
}
