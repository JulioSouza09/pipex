/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_pipes_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcesar-s <jcesar-s@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/13 14:55:25 by jcesar-s          #+#    #+#             */
/*   Updated: 2025/09/14 17:31:01 by jcesar-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

int	*create_pipe(t_pipex *pipex)
{
	int	*pipefd;

	pipefd = ft_calloc(2, sizeof(int));
	if (!pipefd)
		return (NULL);
	if (pipe(pipefd) == -1)
		exit_on_error(pipex, TRUE);
	return (pipefd);
}

int	**create_all_pipes(t_pipex *pipex)
{
	int	i;
	int	**pipefd;

	pipefd = ft_calloc(pipex->cmd_count - 1, sizeof(int *));
	if (!pipefd)
		return (NULL);
	i = 0;
	while (i < pipex->cmd_count - 1)
	{
		pipefd[i] = create_pipe(pipex);
		if (!pipefd[i])
			return (destroy_pipes(pipefd, i), NULL);
		++i;
	}
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

void	destroy_pipes(int **to_free, int position)
{
	int	i;

	i = 0;
	while (i < position)
		free(to_free[i++]);
	free(to_free);
}
