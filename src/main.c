/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcesar-s <jcesar-s@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 15:42:22 by jcesar-s          #+#    #+#             */
/*   Updated: 2025/09/03 10:02:55 by jcesar-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	check_access(const char *pathname, int flags)
{
	if (access(pathname, flags))
	{
		ft_printf_err("pipex: %s: %s\n", strerror(errno), pathname);
		exit(errno);
	}
	return ;
}

int	open_correctly(char *pathname, int flags)
{
	int	fd;

	fd = open(pathname, flags);
	if (fd == -1)
	{
		ft_printf_err("pipex: %s: %s\n", strerror(errno), pathname);
		exit(errno);
	}
	return (fd);
}

int	main(int argc, char **argv)
{
	int	fd_file1;
	int	fd_file2;

	if (argc != 5)
	{
		ft_printf_err("Usage: %s file1 cmd1 cmd2 file2\n", argv[1]);
		return (1);
	}
	check_access(argv[1], R_OK);
	fd_file1 = open_correctly(argv[1], O_RDONLY);
	check_access(argv[4], W_OK);
	fd_file2 = open(argv[4], O_WRONLY | O_CREAT);
	(void)fd_file2;
	(void)fd_file1;
	return (0);
}
