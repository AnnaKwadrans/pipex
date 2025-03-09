#ifndef PIPEX_H
# define PIPEX_H
# include <stdlib.h>
# include <stddef.h>
# include <unistd.h>
# include <stdio.h>


char	**ft_split(char const *s, char c);
void	*ft_calloc(size_t nmemb, size_t size);
size_t	ft_strlen(const char *s);
void	ft_bzero(void *s, size_t n);
size_t	ft_strlcpy(char *dst, const char *src, size_t size);
void    free_array(char **str);

#endif