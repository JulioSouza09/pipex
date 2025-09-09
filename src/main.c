/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcesar-s <jcesar-s@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 15:42:22 by jcesar-s          #+#    #+#             */
/*   Updated: 2025/09/09 18:43:18 by jcesar-s         ###   ########.fr       */
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
	print_matrix("Test", pipex->cmd1);
	int	fds[2];
	int	pid;

	pipe(fds);
	pid = fork();
	if (pid == 0)
	{
		dup2(pipex->fd1, STDIN_FILENO);
		dup2(fds[1], STDOUT_FILENO);
		close(fds[0]);
		close(fds[1]);
		execve(*pipex->cmd1, pipex->cmd1, envp);
	}
	else
	{
		dup2(pipex->fd2, STDOUT_FILENO);
		dup2(fds[0], STDIN_FILENO);
		close(fds[0]);
		close(fds[1]);
		execve(*pipex->cmd2, pipex->cmd2, envp);
		wait(NULL);
	}
	pipex_destroy(pipex);
	return (0);
}
