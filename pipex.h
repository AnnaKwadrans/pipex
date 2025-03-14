/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akwadran <akwadran@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 20:32:35 by akwadran          #+#    #+#             */
/*   Updated: 2025/03/14 21:33:08 by akwadran         ###   ########.fr       */
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
# include "libft/libft.h"
# include <sys/wait.h>
# include <stdio.h>
# include <stdbool.h>

# define IN 0
# define OUT 1
# define RD 0
# define WR 1

int		open_infile(char *infile);
int		open_outfile(char *outfile);
void	child(int files_fds[2], int pipe_fds[2], char *cmd, char **envp);
void	parent(int files_fds[2], int pipe_fds[2], char *cmd, char **envp);

void	exec_cmd(char *cmd, char **envp);
char	**parse_path_var(char **envp);
char	*get_path(char **cmds_array, char **paths_array);
void	free_array(char **str);
void	print_array(char **str);

#endif
