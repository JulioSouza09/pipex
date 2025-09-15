/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_pipes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcesar-s <jcesar-s@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/13 14:55:25 by jcesar-s          #+#    #+#             */
/*   Updated: 2025/09/15 18:22:13 by jcesar-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	*create_pipe(t_pipex *pipex)
{
	int	*pipefd;

	pipefd = ft_calloc(2, sizeof(int));
	if (!pipefd)
		return (NULL);
	if (pipe(pipefd) == -1)
		exit_on_error(pipex, TRUE, EXIT_FAILURE);
	return (pipefd);
}

int	*create_pids(t_pipex *pipex)
{
	int	*pids;

	pids = ft_calloc(pipex->cmd_count, sizeof(int));
	if (!pids)
		return (NULL);
	return (pids);
}
