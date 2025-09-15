/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcesar-s <jcesar-s@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 15:42:22 by jcesar-s          #+#    #+#             */
/*   Updated: 2025/09/15 17:43:36 by jcesar-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int argc, char **argv, char **envp)
{
	int		exit_status;
	t_pipex	*pipex;

	if (argc != 5)
	{
		fd_printf(2, "Usage: %s <file1> cmd1 cmd2 <file2>\n", argv[0]);
		return (3);
	}
	pipex = pipex_init(argc, argv, envp);
	if (!pipex)
		return (4);
	exec_pipe_chain(pipex);
	exit_status = close_and_wait(pipex);
	pipex_destroy(pipex);
	return (exit_status);
}
