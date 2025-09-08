/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcesar-s <jcesar-s@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 09:35:28 by jcesar-s          #+#    #+#             */
/*   Updated: 2025/09/08 13:50:42 by jcesar-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	free_matrix(char **matrix)
{
	int i;

	i = 0;
	while (matrix[i])
		free(matrix[i++]);
	free(matrix[i]);
	free(matrix);
}

int	open_correctly(t_pipex *pipex, char *pathname, int flags, mode_t mode)
{
	int	fd;

	if (mode)
		fd = open(pathname, flags, mode);
	else
		fd = open(pathname, flags);
	if (fd == -1)
	{
		if (pipex)
			free(pipex);
		ft_printf_err("pipex: %s: %s\n", strerror(errno), pathname);
		exit(errno);
	}
	return (fd);
}
