/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akwadran <akwadran@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 20:32:02 by akwadran          #+#    #+#             */
/*   Updated: 2025/03/15 17:48:17 by akwadran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	exec_cmd(char *cmd, char **envp)
{
	char	**cmds_array;
	char	**paths_array;
	char	*path;

	cmds_array = ft_split(cmd, ' ');
	paths_array = parse_path_var(envp);
	path = get_path(cmds_array, paths_array);
	if (paths_array)
		free_array(paths_array);
	if (path)
	{
		execve(path, cmds_array, envp);
		free(path);
		free_array(cmds_array);
		return (perror("Execve failed"));
	}
	else
	{
		free_array(cmds_array);
		ft_putendl_fd("Command not found", 2);
	}
}

char	**parse_path_var(char **envp)
{
	int		i;
	char	**paths_array;

	i = 0;
	while (envp[i])
	{
		if (strncmp(envp[i], "PATH=", 5) == 0 && envp[i][5])
		{
			paths_array = ft_split(envp[i] + 5, ':');
			if (paths_array)
				return (paths_array);
		}
		i++;
	}
	return (NULL);
}

char	*get_path(char **cmds_array, char **paths_array)
{
	int		i;
	char	*aux;
	char	*path;

	if (paths_array == NULL || cmds_array == NULL)
		return (NULL);
	i = 0;
	while (paths_array[i] != NULL)
	{
		if (ft_strncmp(cmds_array[0], paths_array[i], ft_strlen(paths_array[i])) == 0)
			path = ft_strdup(cmds_array[0]);
		else
		{
			aux = ft_strjoin(paths_array[i], "/");
			path = ft_strjoin(aux, cmds_array[0]);
			free(aux);
		}
		if (access(path, X_OK) == 0)
			return (path);
		free(path);
		i++;
	}
	return (NULL);
}

void	free_array(char **str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		free(str[i]);
		i++;
	}
	free(str);
}
