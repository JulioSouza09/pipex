/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_checker_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcesar-s <jcesar-s@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 09:59:40 by jcesar-s          #+#    #+#             */
/*   Updated: 2025/09/15 11:53:54 by jcesar-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

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
char	*handle_error(char *to_free, char *name, int code)
{
	if (to_free)
		free(to_free);
	if (code == ALLOC_ERR)
		fd_printf(2, "pipex: an error ocurred.\n");
	else if (code == NOT_FOUND)
		fd_printf(2, "pipex: command not found: %s\n", name);
	return (NULL);
}

static
char	*get_program_path(char *name, char **split_env)
{
	char		*program_path;
	char		*tmp;
	int			i;

	if (access(name, F_OK) == 0)
		return (ft_strdup(name));
	if (!name || !split_env)
		return (handle_error(NULL, name, ALLOC_ERR));
	tmp = ft_strjoin("/", name);
	if (!tmp)
		return (handle_error(NULL, name, ALLOC_ERR));
	i = 0;
	while (split_env[i])
	{
		program_path = ft_strjoin(split_env[i++], tmp);
		if (!program_path)
			return (handle_error(tmp, name, ALLOC_ERR));
		if (access(program_path, F_OK) == 0)
		{
			handle_error(tmp, name, SUCCESS);
			return (program_path);
		}
		free(program_path);
	}
	return (handle_error(tmp, name, NOT_FOUND));
}

char	**cmd_split(char *cmd)
{
	char	**result;

	result = ft_split(cmd, ' ');
	if (!result)
		return (NULL);
	if (count_words(cmd, ' ') > 0)
		return (result);
	free_matrix(result);
	result = ft_calloc(2, sizeof(char *));
	if (!result)
		return (NULL);
	result[0] = ft_strdup(cmd);
	if (!result[0])
		return (NULL);
	return (result);
}

char	**get_cmd(char *cmd, char **envp)
{
	char	*full_path;
	char	**cmd_name;
	char	**path_env;

	if (!cmd || !envp)
		return (NULL);
	if (!*cmd)
		return (ft_putendl_fd("pipex: permission denied: ", 2), NULL);
	cmd_name = cmd_split(cmd);
	if (!cmd_name)
		return (NULL);
	path_env = ft_split(get_path_env(envp), ':');
	if (!path_env)
		return (free_matrix(cmd_name), NULL);
	full_path = get_program_path(cmd_name[0], path_env);
	free_matrix(path_env);
	if (!full_path)
		return (free_matrix(cmd_name), NULL);
	free(cmd_name[0]);
	cmd_name[0] = full_path;
	return (cmd_name);
}
