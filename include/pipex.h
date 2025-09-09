/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcesar-s <jcesar-s@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/31 17:27:33 by jcesar-s          #+#    #+#             */
/*   Updated: 2025/09/09 12:10:51 by jcesar-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H

# define PIPEX_H

# include <stdio.h>
# include <string.h>
# include <errno.h>
# include <unistd.h>
# include "libft.h"

enum e_error
{
	SUCCESS = 0,
	ALLOC_ERR = -1,
	NOT_FOUND = 1
};

typedef struct s_pipex
{
	int		fd1;
	int		fd2;
	char	**cmd1;
	char	**cmd2;
	char	**envp;
}	t_pipex;

/***** Command checker *****/
char	**get_cmd(char *cmd, char **envp);

/***** Utils *****/
void	free_matrix(char **matrix);
int		open_correctly(t_pipex *pipex, char *pathname, int flags, mode_t mode);

/***** Pipex init *****/
t_pipex	*pipex_init(char **argv, char **envp);
void	pipex_destroy(t_pipex *pipex);

#endif
