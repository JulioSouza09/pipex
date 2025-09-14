/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   case_heredoc_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcesar-s <jcesar-s@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/14 18:43:58 by jcesar-s          #+#    #+#             */
/*   Updated: 2025/09/14 21:08:25 by jcesar-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

static
int	heredoc_to_pipe(char *str, int *read_end)
{
	int		pipefd[2];

	if (pipe(pipefd) == -1)
		return (-1);
	if (str)
	{
		if (fd_printf(pipefd[1], "%s", str) < 0)
			return (-1);
	}
	safe_close(&pipefd[1]);
	free(str);
	*read_end = pipefd[0];
	return (0);
}

static
char	*line_join(char *l1, char *l2)
{
	char	*result;
	char	*to_free;

	to_free = l1;
	result = ft_strjoin(l1, l2);
	if (!result)
		return (NULL);
	if (to_free)
		free(to_free);
	free(l2);
	return (result);
}

int	get_heredoc(char **argv, int *read_end)
{
	char	*limiter;
	char	*line;
	char	*result;

	limiter = ft_strjoin(argv[2], "\n");
	if (!limiter)
		return (1);
	result = NULL;
	while (TRUE)
	{
		ft_printf("pipe heredoc> ");
		line = get_next_line(STDIN_FILENO);
		if (!line)
			return (1);
		if (ft_strcmp(limiter, line) == 0)
		{
			free(line);
			break ;
		}
		result = line_join(result, line);
		if (!result)
			return (1);
	}
	free(limiter);
	return (heredoc_to_pipe(result, read_end));
}
