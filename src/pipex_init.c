/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcesar-s <jcesar-s@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 12:41:33 by jcesar-s          #+#    #+#             */
/*   Updated: 2025/09/13 14:50:11 by jcesar-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

t_pipex	*pipex_init(char **argv, char **envp)
{
	t_pipex	*pipex;

	pipex = ft_calloc(1, sizeof(t_pipex));
	if (!pipex)
		return (NULL);
	pipex->fd1 = open_correctly(pipex, argv[1], O_RDONLY, 0);
	pipex->fd2 = open_correctly(pipex, argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0666);
	pipex->envp = envp;
	return (pipex);
}

void	pipex_destroy(t_pipex *pipex)
{
	close(pipex->fd1);
	close(pipex->fd2);
	free(pipex);
}
