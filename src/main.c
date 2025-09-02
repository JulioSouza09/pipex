/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcesar-s <jcesar-s@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 15:42:22 by jcesar-s          #+#    #+#             */
/*   Updated: 2025/09/02 16:31:47 by jcesar-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	print_usage(char *str)
{
	ft_putstr_fd("Usage: ", 2);
	ft_putstr_fd(str, 2);
	ft_putendl_fd(" file1 cmd1 cmd2 file2", 2);
	return (1);
}

int	main(int argc, char **argv)
{
	if (argc != 4)
		return (print_usage(argv[0]));
	return (0);
}
