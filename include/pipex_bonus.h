/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcesar-s <jcesar-s@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/31 17:27:33 by jcesar-s          #+#    #+#             */
/*   Updated: 2025/09/13 22:16:23 by jcesar-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H

# define PIPEX_H

# include <stdio.h>
# include <string.h>
# include <errno.h>
# include <unistd.h>
# include <sys/wait.h>
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
	int		cmd_count;
	int		*pids;
	int		**pipefd;
	char	**argv;
	char	**cmd;
	char	**envp;
}	t_pipex;

/***** Command checker *****/
char	**get_cmd(char *cmd, char **envp);

/***** Utils *****/
void	free_matrix(char **matrix);
void	exit_on_error(t_pipex *pipex);
int		open_correctly(t_pipex *pipex, char *pathname, int flags, mode_t mode);

/***** Pipex init *****/
t_pipex	*pipex_init(int argc, char **argv, char **envp);
void	pipex_destroy(t_pipex *pipex);

/***** Pipes *****/
void 	close_unused_pipes(t_pipex *pipex, int needed_read, int needed_write);
int		exec_pipe(t_pipex *pipex, int r_from, int w_to, int index);
int		exec_pipe_chain(t_pipex *pipex);

/***** Create pipes *****/
int		**create_all_pipes(t_pipex *pipex);
int		*create_pids(t_pipex *pipex);
void	destroy_pipes(int **to_free, int position);

#endif
