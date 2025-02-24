/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ielmoudd <ielmoudd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/09 15:15:11 by ielmoudd          #+#    #+#             */
/*   Updated: 2025/02/22 16:49:54 by ielmoudd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	free_array_exit(char **cmd)
{
	int	i;

	i = 0;
	while (cmd[i])
	{
		free(cmd[i]);
		i++;
	}
	free(cmd);
	exit(1);
}

void	write_error(char *str)
{
	write(2, "error: ", 7);
	write(2, "command not found: ", 19);
	if (str)
		write(2, str, ft_strlen(str));
	write(2, "\n", 1);
}

int	main(int ac, char **av, char **env)
{
	int	arr[2];

	if (ac != 5)
	{
		write(2, "Error:\n", 7);
		write(2, "Invalid syntax: ", 16);
		write(2, "./pipex infile \"cmd1\" \"cmd2\" outfile\n", 37);
		exit(1);
	}
	if (pipe(arr) == -1)
	{
		perror("Error");
		exit(1);
	}
	fork_f(av, env, arr);
}
