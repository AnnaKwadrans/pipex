#ifndef PIPEX_H
# define PIPEX_H
# include <stdlib.h>
# include <stddef.h>
# include <unistd.h>
# include <stdio.h>
# include <fcntl.h>
# include <string.h>


char	**ft_split(char const *s, char c);
void	*ft_calloc(size_t nmemb, size_t size);
size_t	ft_strlen(const char *s);
void	ft_bzero(void *s, size_t n);
size_t	ft_strlcpy(char *dst, const char *src, size_t size);
void    free_array(char **str);
void    print_array(char **env);

char	**parse_path_var(char **env);
char	*get_path(char *cmd, char **envp);


void	exec(char *cmd, char **env);
char	*my_getenv(char *name, char **env);

void	exit_handler(int n_exit);
int	open_file(char *file, int in_or_out);
void	ft_free_tab(char **tab);

#endif