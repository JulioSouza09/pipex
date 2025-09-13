/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_init_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcesar-s <jcesar-s@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 12:41:33 by jcesar-s          #+#    #+#             */
/*   Updated: 2025/09/13 22:13:05 by jcesar-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

t_pipex	*pipex_init(int argc, char **argv, char **envp)
{
	t_pipex	*pipex;

	pipex = ft_calloc(1, sizeof(t_pipex));
	if (!pipex)
		return (NULL);
	pipex->fd1 = open_correctly(pipex, argv[1], O_RDONLY, 0);
	pipex->fd2 = open_correctly(pipex, argv[argc - 1], O_WRONLY | O_CREAT | O_TRUNC, 0666);
	pipex->cmd_count = argc - 3;
	pipex->pipefd = create_all_pipes(pipex);
	if (!pipex->pipefd)
		return (pipex_destroy(pipex), NULL);
	pipex->pids = create_pids(pipex);
	if (!pipex)
		return (pipex_destroy(pipex), NULL);
	pipex->argv = argv + 2;
	pipex->envp = envp;
	return (pipex);
}

void	pipex_destroy(t_pipex *pipex)
{
	if (!pipex)
		return ;
	close(pipex->fd1);
	close(pipex->fd2);
	if (pipex->pipefd)
	{
		close_unused_pipes(pipex, -1, -1);
		destroy_pipes(pipex->pipefd, pipex->cmd_count - 1);
	}
	if (pipex->pids)
		free(pipex->pids);
	free(pipex);
}
