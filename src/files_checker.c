/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   files_checker.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcesar-s <jcesar-s@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 09:32:34 by jcesar-s          #+#    #+#             */
/*   Updated: 2025/09/08 09:32:47 by jcesar-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static
void	check_access(const char *pathname, int flags)
{
	if (access(pathname, flags))
	{
		ft_printf_err("pipex: %s: %s\n", strerror(errno), pathname);
		exit(errno);
	}
	return ;
}

static
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

int	check_files(char *pathname, int access_flags, int open_flags)
{
	int	fd;

	check_access(pathname, access_flags);
	fd = open_correctly(pathname, open_flags);
	return (fd);
}
