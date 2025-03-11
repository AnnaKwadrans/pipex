#include <unistd.h>

int	main(int argc, char **argv, char **envp)
{
	char	*args1[] = {"infile", "sort", "grep f", "outfile"};

	execve("pipex", args1, envp);
	return (0);
}
