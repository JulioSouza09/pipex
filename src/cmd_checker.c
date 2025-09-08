/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_checker.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcesar-s <jcesar-s@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 09:59:40 by jcesar-s          #+#    #+#             */
/*   Updated: 2025/09/08 10:20:55 by jcesar-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static
char	*get_path_env(char **envp)
{
	const char	*name = "PATH=";
	int			i;
	int			len;

	i = 0;
	len = ft_strlen(name);
	while (1)
	{
		if (ft_strncmp(envp[i], name, len) == 0)
				return (envp[i] + len);
		++i;
	}
	return (NULL);
}

static
char	*handle_error(char *to_free, t_error *status, int code)
{
	if (to_free)
		free(to_free);
	if (status)
		*status = code;
	return (NULL);
}

static
char	*get_program_path(char *name, t_error *status, char **split_env)
{
	char		*program_path;
	char		*tmp;
	int			i;

	if (!name || !split_env || !status)
		return (handle_error(NULL, status, ALLOC_ERR));
	tmp = ft_strjoin("/", name);
	if (!tmp)
		return (handle_error(NULL, status, ALLOC_ERR));
	i = 0;
	while (split_env[i])
	{
		program_path = ft_strjoin(split_env[i++], tmp);
		if (!program_path)
			return (handle_error(tmp, status, ALLOC_ERR));
		if (access(program_path, F_OK) == 0)
			break ;
		free(program_path);
		program_path = NULL;
	}
	if (!program_path)
		return (handle_error(tmp, status, NOT_FOUND));
	handle_error(tmp, status, SUCCESS);
	return (program_path);
}

char	**get_cmd(char *cmd, char **envp, t_error *status)
{
	char	**result;
	char	*path_env;
	char	*program_path;

	if (!cmd || !envp || !status)
		return (NULL);
	path_env = get_path_env(envp);
	if (!path_env)
		return (NULL);
	result = ft_split(cmd, ' ');
	if (!result)
		return (NULL);
	program_path = get_program_path(result[0], status, result);
	if (!program_path)
	{
		free_matrix(result);
		return (NULL);
	}
	free(result[0]);
	result[0] = program_path;
	return (result);
}
