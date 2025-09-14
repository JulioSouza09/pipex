/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcesar-s <jcesar-s@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 15:48:44 by jcesar-s          #+#    #+#             */
/*   Updated: 2025/09/14 17:14:56 by jcesar-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

static
void	exec_child(t_pipex *pipex, int *read_from, int *write_to)
{
	close_unused_pipes(pipex, *read_from, *write_to);
	if (dup2(*read_from, STDIN_FILENO) == -1)
		exit_on_error(pipex, TRUE);
	if (dup2(*write_to, STDOUT_FILENO) == -1)
		exit_on_error(pipex, TRUE);
	safe_close(read_from);
	safe_close(write_to);
	execve(pipex->cmd[0], pipex->cmd, pipex->envp);
	perror("pipex");
}

static
int	exec_pipe(t_pipex *pipex, int *r_from, int *w_to)
{
	int	pid;

	pid = fork();
	if (pid == -1)
		exit_on_error(pipex, TRUE);
	if (pid == 0)
		exec_child(pipex, r_from, w_to);
	return (pid);
}

void	exec_pipe_chain(t_pipex *p)
{
	int	idx;

	idx = 0;
	while (idx < p->cmd_count)
	{
		p->cmd = get_cmd(p->argv[idx], p->envp);
		if (!p->cmd)
			exit_on_error(p, FALSE);
		if (idx == 0)
			p->pids[idx] = exec_pipe(p, &p->fd1, &p->pipefd[idx][1]);
		else if (idx < p->cmd_count - 1)
			p->pids[idx] = exec_pipe(p, &p->pipefd[idx - 1][0],
					&p->pipefd[idx][1]);
		else if (idx == p->cmd_count - 1)
			p->pids[idx] = exec_pipe(p, &p->pipefd[idx - 1][0], &p->fd2);
		free_matrix(p->cmd);
		++idx;
	}
}

int	close_and_wait(t_pipex *p)
{
	int	idx;
	int	status;

	close_unused_pipes(p, -1, -1);
	idx = 0;
	while (idx < p->cmd_count)
		waitpid(p->pids[idx++], &status, 0);
	return (WEXITSTATUS(status));
}
