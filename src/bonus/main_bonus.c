/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcesar-s <jcesar-s@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 15:42:22 by jcesar-s          #+#    #+#             */
/*   Updated: 2025/09/13 22:05:36 by jcesar-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"
#include <sys/wait.h>

int	main(int argc, char **argv, char **envp)
{
	int	exit_status;

	t_pipex	*pipex;

	pipex = pipex_init(argc, argv, envp);
	if (!pipex)
		return (1);
	exit_status = exec_pipe_chain(pipex);
	pipex_destroy(pipex);
	return (exit_status);
}
