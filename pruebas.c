#include "pipex.h"

int main(int argc, char **argv, char **envp)
{
    char    *path;

    path = get_path("ls", envp);
    ft_printf("%s\n", path);
    free(path);
    return (0);
}