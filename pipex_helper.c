/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_helper.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ielmoudd <ielmoudd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/09 16:43:39 by ielmoudd          #+#    #+#             */
/*   Updated: 2025/02/22 18:19:09 by ielmoudd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_dup2(int fd1, int fd2)
{
	if (dup2(fd1, fd2) == -1)
	{
		perror("Error");
		exit(1);
	}
}

void	ft_close(int fd1)
{
	if (close(fd1) == -1)
	{
		perror("Error");
		exit(1);
	}
}

char	*check_paths(char **paths, char **cmd, int exit_code)
{
	char	*command;
	int		i;

	i = 0;
	command = NULL;
	if (!access(cmd[0], X_OK))
		return (ft_strdup(cmd[0]));
	while (paths[i])
	{
		command = ft_strjoin(paths[i], cmd[0]);
		if (!command)
		{
			perror("Error");
			free_array(paths);
			free_array_exit(cmd);
		}
		if (!access(command, X_OK))
			return (command);
		i++;
		free(command);
	}
	write_error(cmd[0]);
	free_array(paths);
	free_array(cmd);
	exit(exit_code);
}

void	check_path_error(char **paths, char **cmd)
{
	if (!paths)
	{
		perror("Error");
		free_array(cmd);
		exit(1);
	}
	else if (!*paths)
	{
		write_error(cmd[0]);
		free(paths);
		free_array_exit(cmd);
	}
}

char	**get_path(char **env, char **cmd)
{
	char	*path;
	char	**paths;
	int		i;

	if (!access(cmd[0], X_OK))
		return (ft_split(".", ':'));
	i = 0;
	path = NULL;
	while (env[i])
	{
		if (!ft_strncmp(env[i], "PATH=", 5))
			path = env[i];
		i++;
	}
	if (!path)
	{
		write_error(cmd[0]);
		free_array(cmd);
		exit(1);
	}
	paths = ft_split(path + 5, ':');
	check_path_error(paths, cmd);
	return (paths);
}
