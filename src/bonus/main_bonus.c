/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcesar-s <jcesar-s@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 15:42:22 by jcesar-s          #+#    #+#             */
/*   Updated: 2025/09/14 22:49:54 by jcesar-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

int	main(int argc, char **argv, char **envp)
{
	int		exit_status;
	t_pipex	*pipex;

	if (ft_strcmp(argv[1], "here_doc") == 0 && argc < 6)
	{
		fd_printf(2, "Usage: %s here_doc LIMITER cmd cmd1 file2\n", argv[0]);
		return (1);
	}
	else if (argc < 5)
	{
		fd_printf(2, "Usage: %s file1 cmd1 cmd2 ... cmdn file2\n", argv[0]);
		return (2);
	}
	pipex = pipex_init(argc, argv, envp);
	if (!pipex)
		return (2);
	exec_pipe_chain(pipex);
	exit_status = close_and_wait(pipex);
	pipex_destroy(pipex);
	return (exit_status);
}
