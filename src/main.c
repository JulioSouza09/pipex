/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcesar-s <jcesar-s@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 15:42:22 by jcesar-s          #+#    #+#             */
/*   Updated: 2025/09/08 16:58:42 by jcesar-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

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
	ft_printf("getting input from %s...\n", argv[1]);
	print_matrix("executing command ", pipex->cmd1);
	print_matrix("sending output to ", pipex->cmd2);
	ft_printf("writing final output to %s...\n", argv[4]);
	pipex_destroy(pipex);
	return (0);
}
