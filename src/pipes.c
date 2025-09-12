/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcesar-s <jcesar-s@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 15:48:44 by jcesar-s          #+#    #+#             */
/*   Updated: 2025/09/11 15:54:45 by jcesar-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static
void	exec_child1(t_pipex *pipex, int *pipefd)
{
	if (dup2(pipex->fd1, STDIN_FILENO) == -1)
		exit_on_error(pipex);
	close(pipex->fd1);
	if (dup2(pipefd[1], STDOUT_FILENO) == -1)
		exit_on_error(pipex);
	close(pipefd[0]);
	close(pipefd[1]);
	execve(*pipex->cmd1, pipex->cmd1, pipex->envp);
	perror("pipex");
}

static
void	exec_child2(t_pipex *pipex, int *pipefd)
{
	if (dup2(pipex->fd2, STDOUT_FILENO) == -1)
		exit_on_error(pipex);
	close(pipex->fd2);
	if (dup2(pipefd[0], STDIN_FILENO) == -1)
		exit_on_error(pipex);
	close(pipefd[0]);
	close(pipefd[1]);
	execve(*pipex->cmd2, pipex->cmd2, pipex->envp);
	perror("pipex");
}

void	exec_pipe(t_pipex *pipex)
{
	int	pipefd[2];
	int	status;
	int	pid1;
	int	pid2;

	if (pipe(pipefd) == -1)
		exit_on_error(pipex);
	pid1 = fork();
	if (pid1 == -1)
		exit_on_error(pipex);
	if (pid1 == 0)
	{
		exec_child1(pipex, pipefd);
	}
	pid2 = fork();
	if (pid2 == -1)
		exit_on_error(pipex);
	if (pid2 == 0)
	{
		exec_child2(pipex, pipefd);
	}
	close(pipefd[0]);
	close(pipefd[1]);
	waitpid(pid1, &status, 0);
	waitpid(pid2, &status, 0);
}
