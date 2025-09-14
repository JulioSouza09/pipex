/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcesar-s <jcesar-s@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/31 17:27:33 by jcesar-s          #+#    #+#             */
/*   Updated: 2025/09/14 18:51:06 by jcesar-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H

# define PIPEX_H
# define TRUE 1
# define FALSE 0

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
void	exit_on_error(t_pipex *pipex, int print_error);
void	safe_close(int *fd_addr);
void 	close_unused_pipes(t_pipex *pipex, int needed_read, int needed_write);
int		open_correctly(t_pipex *pipex, char *pathname, int flags, mode_t mode);

/***** Pipex init *****/
t_pipex	*pipex_init(int argc, char **argv, char **envp);
void	pipex_destroy(t_pipex *pipex);

/***** Pipes *****/
void	exec_pipe_chain(t_pipex *pipex);
int		close_and_wait(t_pipex *p);

/***** Create pipes *****/
int		*create_pipe(t_pipex *pipex);
int		**create_all_pipes(t_pipex *pipex);
int		*create_pids(t_pipex *pipex);
void	destroy_pipes(int **to_free, int position);

/***** Case heredoc *****/
int	get_heredoc(char **argv, int *read_end);

#endif
