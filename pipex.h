/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akwadran <akwadran@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 20:32:35 by akwadran          #+#    #+#             */
/*   Updated: 2025/03/11 20:45:46 by akwadran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H
# include <stdlib.h>
# include <stddef.h>
# include <unistd.h>
# include <stdio.h>
# include <fcntl.h>
# include <string.h>

void	child_process(int in_fd, int pipe_fds[2], char *cmd, char **envp);
void	parent_process(int out_fd, int pipe_fds[2], char *cmd, char **envp);
void	exec_cmd(char *cmd, char **envp);

char	**parse_path_var(char **envp);
char	*get_path(char *cmd, char **paths_array);
void	free_array(char **str);

#endif
