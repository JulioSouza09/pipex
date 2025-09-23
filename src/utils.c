/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcesar-s <jcesar-s@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 09:35:28 by jcesar-s          #+#    #+#             */
/*   Updated: 2025/09/16 12:33:48 by jcesar-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	free_matrix(char **matrix)
{
	int	i;

	if (!matrix)
		return ;
	i = 0;
	while (matrix[i])
		free(matrix[i++]);
	free(matrix[i]);
	free(matrix);
}

int	open_correctly(char *pathname, int flags, mode_t mode)
{
	int	fd;

	fd = open(pathname, flags, mode);
	if (fd == -1)
	{
		fd_printf(2, "pipex: %s: %s\n", strerror(errno), pathname);
		return (-1);
	}
	return (fd);
}

void	exit_on_error(t_pipex *pipex, int print_error, int exit_code)
{
	if (print_error)
		perror("pipex");
	if (pipex->delete_file)
		unlink(pipex->outfile_name);
	pipex_destroy(pipex);
	exit(exit_code);
}

void	safe_close(int *fd_addr)
{
	if (*fd_addr != -1)
	{
		close(*fd_addr);
		*fd_addr = -1;
	}
}

void	close_unused_pipes(t_pipex *pipex, int needed_read, int needed_write)
{
	if (pipex->pipefd[0] != needed_read)
		safe_close(&pipex->pipefd[0]);
	if (pipex->pipefd[1] != needed_write)
		safe_close(&pipex->pipefd[1]);
	if (needed_read != pipex->fd1)
		safe_close(&pipex->fd1);
	if (needed_write != pipex->fd2)
		safe_close(&pipex->fd2);
}
