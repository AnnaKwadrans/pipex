/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akwadran <akwadran@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 20:32:02 by akwadran          #+#    #+#             */
/*   Updated: 2025/03/11 20:45:25 by akwadran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	**parse_path_var(char **envp)
{
	int		i;
	char	**paths;

	i = 0;
	while (envp[i])
	{
		if (strncmp(envp[i], "PATH=", 5) == 0 && envp[i][5])
		{
			paths = ft_split(envp[i] + 5, ':');
			if (paths)
				return (paths);
		}
		i++;
	}
	return (NULL);
}

char	*get_path(char *cmd, char **paths_array)
{
	int		i;
	char	*aux;
	char	*path;

	if (paths_array == NULL)
		return (NULL);
	i = 0;
	while (paths_array[i] != NULL)
	{
		aux = ft_strjoin(paths_array[i], "/");
		path = ft_strjoin(aux, cmd);
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
