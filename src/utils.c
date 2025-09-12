/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcesar-s <jcesar-s@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 09:35:28 by jcesar-s          #+#    #+#             */
/*   Updated: 2025/09/11 15:54:22 by jcesar-s         ###   ########.fr       */
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
		if (pipex)
			free(pipex);
		fd_printf(2, "pipex: %s: %s\n", strerror(errno), pathname);
		exit(errno);
	}
	return (fd);
}

void	exit_on_error(t_pipex *pipex)
{
	perror("pipex");
	pipex_destroy(pipex);
	exit(3);

}
