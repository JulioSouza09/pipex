/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_init_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcesar-s <jcesar-s@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 12:41:33 by jcesar-s          #+#    #+#             */
/*   Updated: 2025/09/15 16:39:53 by jcesar-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

static
void	find_heredoc(t_pipex *pipex, int argc, char **argv)
{
	int	exit_code;

	if (ft_strcmp(argv[1], "here_doc") != 0)
	{
		pipex->fd1 = open_correctly(argv[1], O_RDONLY, 0);
		pipex->cmd_count = argc - 3;
		pipex->argv_offset = 2;
		pipex->is_heredoc = FALSE;
		return ;
	}
	exit_code = get_heredoc(argv, &pipex->fd1);
	if (exit_code == -1)
		exit_on_error(pipex, TRUE, EXIT_FAILURE);
	else if (exit_code == 1)
		exit_on_error(pipex, FALSE, EXIT_FAILURE);
	pipex->cmd_count = argc - 4;
	pipex->argv_offset = 3;
	pipex->is_heredoc = TRUE;
}

t_pipex	*pipex_init(int argc, char **argv, char **envp)
{
	t_pipex	*pipex;

	pipex = ft_calloc(1, sizeof(t_pipex));
	if (!pipex)
		return (NULL);
	pipex->delete_file = FALSE;
	pipex->outfile_name = argv[argc - 1];
	pipex->argv = argv;
	find_heredoc(pipex, argc, argv);
	pipex->pipefd = create_all_pipes(pipex);
	if (!pipex->pipefd)
		return (pipex_destroy(pipex), NULL);
	pipex->pids = create_pids(pipex);
	if (!pipex->pids)
		return (pipex_destroy(pipex), NULL);
	pipex->envp = envp;
	return (pipex);
}

void	pipex_destroy(t_pipex *pipex)
{
	if (!pipex)
		return ;
	if (pipex->fd1 > 2)
		safe_close(&pipex->fd1);
	if (pipex->fd2 > 2)
		safe_close(&pipex->fd2);
	if (pipex->cmd)
		free_matrix(pipex->cmd);
	if (pipex->pipefd)
	{
		close_unused_pipes(pipex, -1, -1);
		destroy_pipes(pipex->pipefd, pipex->cmd_count - 1);
	}
	if (pipex->pids)
		free(pipex->pids);
	free(pipex);
}
