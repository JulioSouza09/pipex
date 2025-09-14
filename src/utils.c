/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcesar-s <jcesar-s@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 09:35:28 by jcesar-s          #+#    #+#             */
/*   Updated: 2025/09/14 22:30:50 by jcesar-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

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
		fd_printf(2, "pipex: %s: %s\n", pathname, strerror(errno));
		if (pipex)
			exit_on_error(pipex, FALSE);
	}
	return (fd);
}

void	exit_on_error(t_pipex *pipex, int print_error)
{
	if (print_error)
		perror("pipex");
	if (pipex->outfile)
		unlink(pipex->outfile);
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
