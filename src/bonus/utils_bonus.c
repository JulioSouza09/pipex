/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcesar-s <jcesar-s@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 09:35:28 by jcesar-s          #+#    #+#             */
/*   Updated: 2025/09/14 20:43:38 by jcesar-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	free_matrix(char **matrix)
{
	int	i;

	i = 0;
	while (matrix[i])
		free(matrix[i++]);
	free(matrix[i]);
	free(matrix);
}

int	open_correctly(t_pipex *pipex, char *pathname, int flags, mode_t mode)
{
	int	fd;

	fd = open(pathname, flags, mode);
	if (fd == -1)
	{
		if (pipex)
			free(pipex);
		fd_printf(2, "pipex: %s: %s\n", strerror(errno), pathname);
		exit(EXIT_FAILURE);
	}
	return (fd);
}

void	exit_on_error(t_pipex *pipex, int print_error)
{
	if (print_error)
		perror("pipex");
	unlink(pipex->argv[pipex->cmd_count]);
	pipex_destroy(pipex);
	exit(EXIT_FAILURE);
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
	int	i;

	i = 0;
	while (i < pipex->cmd_count - 1)
	{
		if (pipex->pipefd[i][0] != needed_read)
			safe_close(&pipex->pipefd[i][0]);
		if (pipex->pipefd[i][1] != needed_write)
			safe_close(&pipex->pipefd[i][1]);
		++i;
	}
}
