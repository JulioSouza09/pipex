/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcesar-s <jcesar-s@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 15:42:22 by jcesar-s          #+#    #+#             */
/*   Updated: 2025/09/14 18:43:40 by jcesar-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

int	main(int argc, char **argv, char **envp)
{
	int	exit_status;

	t_pipex	*pipex;

	pipex = pipex_init(argc, argv, envp);
	if (!pipex)
		return (1);
	exec_pipe_chain(pipex);
	exit_status = close_and_wait(pipex);
	pipex_destroy(pipex);
	return (exit_status);
}
