/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcesar-s <jcesar-s@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 15:48:44 by jcesar-s          #+#    #+#             */
/*   Updated: 2025/09/16 12:25:51 by jcesar-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

static
void	exec_child(t_pipex *pipex, int *read_from, int *write_to)
{
	if (*write_to == -1)
		exit_on_error(pipex, FALSE, EXIT_FAILURE);
	close_unused_pipes(pipex, *read_from, *write_to);
	if (dup2(*read_from, STDIN_FILENO) == -1)
		exit_on_error(pipex, TRUE, EXIT_FAILURE);
	if (dup2(*write_to, STDOUT_FILENO) == -1)
		exit_on_error(pipex, TRUE, EXIT_FAILURE);
	safe_close(read_from);
	safe_close(write_to);
	if (!pipex->cmd)
		exit_on_error(pipex, FALSE, 127);
	execve(pipex->cmd[0], pipex->cmd, pipex->envp);
	exit_on_error(pipex, FALSE, EXIT_FAILURE);
}

static
int	exec_pipe(t_pipex *pipex, int *r_from, int *w_to)
{
	int	pid;

	if (*r_from == -1)
		return (-1);
	pid = fork();
	if (pid == -1)
		exit_on_error(pipex, TRUE, EXIT_FAILURE);
	if (pid == 0)
		exec_child(pipex, r_from, w_to);
	return (pid);
}

static
void	open_and_exec(t_pipex *p, int idx)
{
	if (p->is_heredoc)
		p->fd2 = open_correctly(p->outfile_name,
				O_WRONLY | O_CREAT | O_APPEND, 0666);
	else
		p->fd2 = open_correctly(p->outfile_name,
				O_WRONLY | O_CREAT | O_TRUNC, 0666);
	p->pids[idx] = exec_pipe(p, &p->pipefd[idx - 1][0], &p->fd2);
}

void	exec_pipe_chain(t_pipex *p)
{
	int	idx;
	int	argv_offset;

	idx = 0;
	while (idx < p->cmd_count)
	{
		argv_offset = p->argv_offset;
		p->cmd = get_cmd(p->argv[idx + argv_offset], p->envp);
		if (idx == 0)
			p->pids[idx] = exec_pipe(p, &p->fd1, &p->pipefd[idx][1]);
		else if (idx < p->cmd_count - 1)
			p->pids[idx] = exec_pipe(p, &p->pipefd[idx - 1][0],
					&p->pipefd[idx][1]);
		else if (idx == p->cmd_count - 1)
			open_and_exec(p, idx);
		if (p->cmd)
		{
			free_matrix(p->cmd);
			p->cmd = NULL;
		}
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
