/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcesar-s <jcesar-s@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 15:48:44 by jcesar-s          #+#    #+#             */
/*   Updated: 2025/09/13 22:20:08 by jcesar-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

static
void	exec_child1(t_pipex *pipex, int read_from, int *pipefd, int idx)
{
	char	**cmd;

	cmd = get_cmd(pipex->argv[idx], pipex->envp);
	if (dup2(read_from, STDIN_FILENO) == -1)
		exit_on_error(pipex);
	if (dup2(pipefd[1], STDOUT_FILENO) == -1)
		exit_on_error(pipex);
	close(read_from);
	close(pipefd[1]);
	close(pipefd[0]);
	if (idx > 0)
		return ;
	execve(cmd[0], cmd, pipex->envp);
	perror("pipex");
}

static
void	exec_child2(t_pipex *pipex, int write_to, int *pipefd, int idx)
{
	char	**cmd;

	cmd = get_cmd(pipex->argv[idx], pipex->envp);
	if (dup2(write_to, STDOUT_FILENO) == -1)
		exit_on_error(pipex);
	if (dup2(pipefd[0], STDIN_FILENO) == -1)
		exit_on_error(pipex);
	close(write_to);
	close(pipefd[0]);
	close(pipefd[1]);
	execve(cmd[0], cmd, pipex->envp);
	perror("pipex");
}

int	exec_pipe(t_pipex *pipex, int r_from, int w_to, int idx)
{
	int	status;
	int	pid1;
	int	pid2;

	pid1 = fork();
	if (pid1 == -1)
		exit_on_error(pipex);
	if (pid1 == 0)
		exec_child1(pipex, r_from, pipex->pipefd[idx], idx);
	pid2 = fork();
	if (pid2 == -1)
		exit_on_error(pipex);
	if (pid2 == 0)
		exec_child2(pipex, w_to, pipex->pipefd[idx], idx + 1);
	if (idx > 0)
		close(pipex->pipefd[idx][0]);
	close(pipex->pipefd[idx][1]);
	waitpid(pid1, &status, 0);
	waitpid(pid2, &status, 0);
	return (WEXITSTATUS(status));
}

void close_unused_pipes(t_pipex *pipex, int needed_read, int needed_write)
{
    int i;
    
	i = 0;
	while (i < pipex->cmd_count - 1)
	{
        if (pipex->pipefd[i][0] != needed_read)
            close(pipex->pipefd[i][0]);
        if (pipex->pipefd[i][1] != needed_write)
            close(pipex->pipefd[i][1]);
		++i;
    }
}

static
void	exec_child12(t_pipex *pipex, int read_from, int write_to)
{
	close_unused_pipes(pipex, read_from, write_to);
	if (dup2(read_from, STDIN_FILENO) == -1)
		exit_on_error(pipex);
	if (dup2(write_to, STDOUT_FILENO) == -1)
		exit_on_error(pipex);
	close(read_from);
	close(write_to);
	execve(pipex->cmd[0], pipex->cmd, pipex->envp);
	perror("pipex");
}

int	exec_pipe2(t_pipex *pipex, int r_from, int w_to, int idx)
{
	int	pid;

	pid = fork();
	if (pid == -1)
		exit_on_error(pipex);
	if (pid == 0)
		exec_child12(pipex, r_from, w_to);
	if (idx > 0)
		close(pipex->pipefd[idx - 1][0]);
	if (idx < pipex->cmd_count - 1)
		close(pipex->pipefd[idx][1]);
	return (pid);
}

int	exec_pipe_chain(t_pipex *p)
{
	int	idx;
	int	idx2;
	int	status;

	idx = 0;
	while (idx < p->cmd_count)
	{
		p->cmd = get_cmd(p->argv[idx], p->envp);
		if (!p->cmd)
		{
			pipex_destroy(p);
			exit(EXIT_FAILURE);
		}
		if (idx == 0)
			p->pids[idx] = exec_pipe2(p, p->fd1, p->pipefd[idx][1], idx);
		else if (idx < p->cmd_count - 1)
			p->pids[idx] = exec_pipe2(p, p->pipefd[idx - 1][0],
					p->pipefd[idx][1], idx);
		else if (idx == p->cmd_count - 1)
			p->pids[idx] = exec_pipe2(p, p->pipefd[idx - 1][0], p->fd2,
					idx);
		free_matrix(p->cmd);
		++idx;
	}
	idx2 = 0;
	while (idx2 < p->cmd_count)
		waitpid(p->pids[idx2++], &status, 0);
	return (WEXITSTATUS(status));
}
