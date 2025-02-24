/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork_f.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ielmoudd <ielmoudd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 14:10:10 by ielmoudd          #+#    #+#             */
/*   Updated: 2025/02/22 16:51:11 by ielmoudd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	get_exit_code(pid_t pid1, pid_t pid2)
{
	int	code1;
	int	code2;
	int	status;

	waitpid(pid1, &code1, 0);
	waitpid(pid2, &code2, 0);
	if (WIFSIGNALED(code2))
		status = 128 + WTERMSIG(code2);
	else
		status = WEXITSTATUS(code2);
	exit(status);
}

char	**ft_split_cmd(char *str)
{
	char	**cmd;

	cmd = ft_split(str, ' ');
	if (!cmd)
	{
		perror("Error");
		exit(1);
	}
	else if (!*cmd)
	{
		write_error(str);
		free_array_exit(cmd);
	}
	return (cmd);
}

void	fork_p2(int *arr, char **av, char **env)
{
	char	*pathname;
	char	**cmd;
	int		fd2;
	char	**paths;

	fd2 = open(av[4], O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd2 < 0)
	{
		perror("error");
		exit(1);
	}
	ft_dup2(arr[0], STDIN_FILENO);
	ft_dup2(fd2, STDOUT_FILENO);
	ft_close(fd2);
	ft_close(arr[0]);
	ft_close(arr[1]);
	cmd = ft_split_cmd(av[3]);
	paths = get_path(env, cmd);
	pathname = check_paths(paths, cmd, 127);
	execve(pathname, cmd, env);
	perror("Error");
	free_array(cmd);
	free(pathname);
	free_array_exit(paths);
}

void	fork_p1(int *arr, char **av, char **env)
{
	char	*pathname;
	int		fd1;
	char	**cmd;
	char	**paths;

	fd1 = open(av[1], O_RDONLY);
	if (fd1 < 0)
	{
		perror("error");
		exit(1);
	}
	ft_dup2(fd1, STDIN_FILENO);
	ft_dup2(arr[1], STDOUT_FILENO);
	ft_close(fd1);
	ft_close(arr[0]);
	ft_close(arr[1]);
	cmd = ft_split_cmd(av[2]);
	paths = get_path(env, cmd);
	pathname = check_paths(paths, cmd, 127);
	execve(pathname, cmd, env);
	perror("Error");
	free_array(cmd);
	free(pathname);
	free_array_exit(paths);
}

void	fork_f(char **av, char **env, int *arr)
{
	pid_t	pid1;
	pid_t	pid2;

	pid1 = fork();
	if (pid1 == -1)
	{
		perror("Error");
		exit(1);
	}
	else if (pid1 == 0)
		fork_p1(arr, av, env);
	pid2 = fork();
	if (pid2 == -1)
	{
		perror("Error");
		exit(1);
	}
	else if (pid2 == 0)
		fork_p2(arr, av, env);
	ft_close(arr[0]);
	ft_close(arr[1]);
	get_exit_code(pid1, pid2);
}
