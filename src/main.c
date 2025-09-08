/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcesar-s <jcesar-s@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 15:42:22 by jcesar-s          #+#    #+#             */
/*   Updated: 2025/09/08 13:47:30 by jcesar-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int argc, char **argv, char **envp)
{
	t_pipex	*pipex;

	if (argc != 5)
	{
		ft_printf_err("Usage: %s file1 cmd1 cmd2 file2\n", argv[1]);
		return (1);
	}
	pipex = pipex_init(argv, envp);
	if (!pipex)
		return (2);
	ft_printf("getting input from %s...\n", argv[1]);
	ft_printf("executing command %s...\n", *pipex->cmd1);
	ft_printf("sending output to %s...\n", *pipex->cmd2);
	ft_printf("writing final output to %s...\n", argv[4]);
	pipex_destroy(pipex);
	return (0);
}
