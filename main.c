/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akwadran <akwadran@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 20:31:05 by akwadran          #+#    #+#             */
/*   Updated: 2025/03/22 11:13:49 by akwadran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include <stdio.h>

int	main(int argc, char **argv, char **envp)
{
	int		pipe_fds[2];
	int		files_fds[2];
	pid_t	pid1;
	pid_t	pid2;

	if (argc != 5)
		return (ft_printf("Error: incorrect agruments\n"), 1);
	files_fds[IN] = open_infile(argv[1]);
	files_fds[OUT] = open_outfile(argv[4]);
	if (pipe(pipe_fds) < 0)
		return (perror("Pipe failed"), 1);
	pid1 = fork();
	if (pid1 < 0)
		return (perror("Fork failed"), 1);
	else if (pid1 == 0)
		child(files_fds, pipe_fds, argv[2], envp);
	else if (pid1 > 0)
		parent(files_fds, pipe_fds, argv[3], envp);
	return (0);
}

int	open_infile(char *infile)
{
	int	fd;

	if (access(infile, F_OK) == -1 || access(infile, R_OK) == -1)
	{
		perror("Cannot access infile");
		return (-1);
	}
	fd = open(infile, O_RDONLY);
	if (fd == -1)
		perror("Open failed");
	return (fd);
}

int	open_outfile(char *outfile)
{
	int	fd;

	if (access(outfile, F_OK) == 0 && access(outfile, W_OK) == -1)
	{
		perror("Cannot access outfile");
		return (-1);
	}
	fd = open(outfile, O_WRONLY | O_CREAT | O_TRUNC, 0666);
	if (fd == -1)
		perror("Open failed");
	return (fd);
}

void	child(int files_fds[2], int pipe_fds[2], char *cmd, char **envp)
{
	if (files_fds[IN] < 0)
	{
		close(pipe_fds[RD]);
		close(files_fds[OUT]);
		close(pipe_fds[WR]);
		exit(1);
	}
	else
	{
		close(pipe_fds[RD]);
		close(files_fds[OUT]);
		dup2(files_fds[IN], STDIN_FILENO);
		close(files_fds[IN]);
		dup2(pipe_fds[WR], STDOUT_FILENO);
		close(pipe_fds[WR]);
		exec_cmd(cmd, envp);
		exit(1);
	}
}

void	parent(int files_fds[2], int pipe_fds[2], char *cmd, char **envp)
{
	wait(NULL);
	if (files_fds[OUT] < 0)
	{
		close(pipe_fds[RD]);
		close(files_fds[IN]);
		close(pipe_fds[WR]);
		exit(1);
	}
	close(pipe_fds[WR]);
	close(files_fds[IN]);
	dup2(pipe_fds[RD], STDIN_FILENO);
	close(pipe_fds[RD]);
	dup2(files_fds[OUT], STDOUT_FILENO);
	close(files_fds[OUT]);
	exec_cmd(cmd, envp);
	exit(1);
}
