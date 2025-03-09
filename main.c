#include "pipex.h"
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>




int	main(int argc, char **argv, char **envp)
{
	int	infile_fd;
	int outfile_fd;
	int	fds[2];
	pid_t	pid;
	char	*cmds1[] = {"ls", NULL};
	char	*cmds2[] = {"wc", "-l", NULL};

	//print_array(envp);
	infile_fd = open("infile", O_RDONLY);
	outfile_fd = open("outfile", O_WRONLY | O_CREAT, 0644);

	//dup2(infile_fd, 0);
	//dup2(outfile_fd, 1);
	if (pipe(fds) < 0)
	{
		perror("Pipe failed");
		exit (1);
	}
	pid = fork();
	if (pid < 0)
	{
		perror("Fork failed");
		exit (1);
	}
	else if (pid == 0) // child
	{
		printf("child process\n");
		dup2(infile_fd, 0);
		//dup2(0, fds[0]);
		dup2(fds[1], 1);
		close(fds[0]);
		close(fds[1]);
		//execve("grep", "fil", envp);
		exec("grep Aug", envp);
		printf("child check\n");
	}
	else if (pid > 0) // parent
	{
		printf("parent process\n");
		//dup2(1, fds[1]);
		dup2(fds[0], 0);
		dup2(outfile_fd, 1);
		close(fds[0]);
		close(fds[1]);
		//execve("sort", "NULL", envp);
		exec("sort", envp);
		printf("parent check\n");
	}
	//free_array(cmds1);
	//free_array(cmds2);
	return (0);
}