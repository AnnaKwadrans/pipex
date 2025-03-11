/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akwadran <akwadran@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 20:31:05 by akwadran          #+#    #+#             */
/*   Updated: 2025/03/11 21:34:54 by akwadran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

//unlink, wait, waitpid
int	main(int argc, char **argv, char **envp)
{
	int		in_fd;
	int		out_fd;
	int		pipe_fds[2];
	pid_t	pid;

	if (argc != 5)
		return (ft_printf("Error: incorrect agruments\n"), 1);
	in_fd = open(argv[1], O_RDONLY);
	out_fd = open(argv[4], O_WRONLY | O_CREAT);
	if (pipe(pipe_fds) < 0)
		return (perror("Pipe failed"), 1);
	pid = fork();
	if (pid < 0)
		return (perror("Fork failed"), 1);
	else if (pid == 0)
		child_process(in_fd, pipe_fds, argv[2], envp);
	else if (pid > 0)
		parent_process(out_fd, pipe_fds, argv[3], envp);
	close(in_fd);
	close(out_fd);
	return (0);
}

void	child_process(int in_fd, int pipe_fds[2], char *cmd, char **envp)
{
	dup2(in_fd, 0);
	dup2(pipe_fds[1], 1);
	close(pipe_fds[0]);
	close(pipe_fds[1]);
	exec_cmd(cmd, envp);
}

void	parent_process(int out_fd, int pipe_fds[2], char *cmd, char **envp)
{
	dup2(pipe_fds[0], 0);
	dup2(out_fd, 1);
	close(pipe_fds[0]);
	close(pipe_fds[1]);
	exec_cmd(cmd, envp);
}

void	exec_cmd(char *cmd, char **envp)
{
	char	**cmds_array;
	char	**paths_array;
	char	*path;

	cmds_array = ft_split(cmd, ' ');
	paths_array = parse_path_var(envp);
	path = get_path(cmds_array[0], paths_array);
	execve(path, cmds_array, envp);
}
