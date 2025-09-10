/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcesar-s <jcesar-s@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 15:42:22 by jcesar-s          #+#    #+#             */
/*   Updated: 2025/09/10 11:11:47 by jcesar-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include <sys/wait.h>

void	print_matrix(char *outer_text, char **matrix)
{
	int	i;

	i = 0;
	ft_printf("%s", outer_text);
	while (matrix[i])
		ft_printf("%s ", matrix[i++]);
	ft_printf("...\n");
}

void	exit_on_error(t_pipex *pipex)
{
	perror("pipex");
	pipex_destroy(pipex);
	exit(3);

}

void	handle_pipes(t_pipex *pipex)
{
	int	fds[2];
	int	pid;

	if (pipe(fds) == -1)
		exit_on_error(pipex);
	pid = fork();
	if (pid == -1)
		exit_on_error(pipex);
	if (pid == 0)
	{
		if (dup2(pipex->fd1, STDIN_FILENO) == -1)
			exit_on_error(pipex);
		close(pipex->fd1);
		if (dup2(fds[1], STDOUT_FILENO) == -1)
			exit_on_error(pipex);
		close(fds[0]);
		close(fds[1]);
		execve(*pipex->cmd1, pipex->cmd1, pipex->envp);
		perror("pipex");
	}
	else
	{
		if (dup2(pipex->fd2, STDOUT_FILENO) == -1)
			exit_on_error(pipex);
		close(pipex->fd2);
		if (dup2(fds[0], STDIN_FILENO) == -1)
			exit_on_error(pipex);
		close(fds[0]);
		close(fds[1]);
		wait(NULL);
		execve(*pipex->cmd2, pipex->cmd2, pipex->envp);
		perror("pipex");
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_pipex	*pipex;

	if (argc != 5)
	{
		fd_printf(2, "Usage: %s file1 cmd1 cmd2 file2\n", argv[1]);
		return (1);
	}
	pipex = pipex_init(argv, envp);
	if (!pipex)
		return (2);
	handle_pipes(pipex);
	pipex_destroy(pipex);
	return (0);
}
