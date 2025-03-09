/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akwadran <akwadran@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/16 15:57:42 by akwadran          #+#    #+#             */
/*   Updated: 2025/03/01 17:37:45 by akwadran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*Argumentos archivo1 comando1 comando2 archivo2
Funciones autorizadas
• open, close, read, write,
malloc, free, perror,
strerror, access, dup, dup2,
execve, exit, fork, pipe,
unlink, wait, waitpid
• ft_printf and any equivalent
YOU coded*/

#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>

int	main(int argc, char **argv)
{
	int	infile_fd;
	int	outfile_fd;
	char	*buffer;
	int	b_read;
	int	buffer_size;

	if (access(argv[1], F_OK) == -1 || access(argv[1], R_OK) == -1
		|| access(argv[2], F_OK == -1 || access(argv[2], W_OK) == -1))
		// puedo poner directamente access("infile")
	{
		perror("Error");
		printf("%s", strerror(errno));
		printf("%d", errno);
		return (1);
	}

	infile_fd = open(argv[1], O_RDONLY);
	outfile_fd = open(argv[2], O_WRONLY);
	if (infile_fd == -1 || outfile_fd == -1)
		return (1);
	buffer_size = 0;
	buffer = malloc(sizeof(char));
	while (read(infile_fd, buffer, sizeof(char)) != 0)
		buffer_size++;
	free(buffer);
	close(infile_fd);
	infile_fd = open(argv[1], O_RDONLY);
	buffer = malloc(buffer_size * sizeof(char));
	b_read = read(infile_fd, buffer, buffer_size);
	//dup2(outfile_fd, STDOUT_FILENO);
	dup2(outfile_fd, 1);
	printf("QWERTYUIOPASDFGHJKL\n%d %d", infile_fd, outfile_fd);
	//write(outfile_fd, buffer, b_read);
	free(buffer);
	close(infile_fd);
	close(outfile_fd);
	return (0);
}
