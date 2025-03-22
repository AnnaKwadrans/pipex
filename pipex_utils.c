/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akwadran <akwadran@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 20:32:02 by akwadran          #+#    #+#             */
/*   Updated: 2025/03/22 11:53:34 by akwadran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	exec_cmd(char *cmd, char **envp)
{
	char	**cmd_tab;
	char	**path_tab;
	char	*path;

	cmd_tab = ft_split(cmd, ' ');
	path_tab = parse_path_var(envp);
	path = get_path(cmd_tab, path_tab);
	if (path_tab)
		free_array(path_tab);
	if (path)
	{
		execve(path, cmd_tab, envp);
		free(path);
		free_array(cmd_tab);
		return (perror("Execve failed"));
	}
	else
	{
		free_array(cmd_tab);
		ft_putendl_fd("Command not found", 2);
		exit(127);
	}
}

char	**parse_path_var(char **envp)
{
	int		i;
	char	**path_tab;

	if (envp == NULL)
		return (NULL);
	i = 0;
	while (envp[i])
	{
		if (strncmp(envp[i], "PATH=", 5) == 0 && envp[i][5])
		{
			path_tab = ft_split(envp[i] + 5, ':');
			if (path_tab)
				return (path_tab);
		}
		i++;
	}
	return (NULL);
}

char	*get_path(char **cmd_tab, char **path_tab)
{
	int		i;
	char	*aux;
	char	*path;

	if (path_tab == NULL || cmd_tab == NULL)
		return (NULL);
	if (!cmd_tab[0])
		cmd_tab[0] = ft_strdup("cat");
	i = 0;
	while (path_tab[i] != NULL)
	{
		if (ft_strncmp(cmd_tab[0], path_tab[i], ft_strlen(path_tab[i])) == 0)
			path = ft_strdup(cmd_tab[0]);
		else
		{
			aux = ft_strjoin(path_tab[i], "/");
			path = ft_strjoin(aux, cmd_tab[0]);
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
