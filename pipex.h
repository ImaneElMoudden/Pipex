/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ielmoudd <ielmoudd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/09 16:43:08 by ielmoudd          #+#    #+#             */
/*   Updated: 2025/02/20 22:01:29 by ielmoudd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/wait.h>
# include <unistd.h>

// pipex helper:
char	*check_paths(char **paths, char **cmd, int exit_code);
void	check_path_error(char **paths, char **cmd);
char	**get_path(char **env, char **cmd);
void	free_array_exit(char **cmd);
void	ft_dup2(int fd1, int fd2);
void	write_error(char *str);
void	ft_close(int fd1);

// pipex:
void	fork_p1(int *arr, char **av, char **env);
void	fork_p2(int *arr, char **av, char **env);
void	fork_f(char **av, char **env, int *arr);
void	get_exit_code(pid_t pid1, pid_t pid2);
char	**ft_split_cmd(char *str);

// libft helper:
int		ft_strncmp(const char *s1, const char *s2, size_t n);
char	*ft_strjoin(char const *s1, char const *s2);
size_t	ft_strlen(const char *s);
void	free_array(char **cmd);
char	*ft_strdup(char *s);

// Split:
char	**ft_split(char const *s, char c);

#endif