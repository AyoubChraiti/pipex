/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achraiti <achraiti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/28 15:20:41 by achraiti          #+#    #+#             */
/*   Updated: 2024/02/16 20:52:47 by achraiti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*get_path(t_list *x, int t)
{
	char	*try;
	int		i;

	i = 0;
	x->path_var = get_env(x->env);
	x->paths = ft_split(x->path_var, ':');
	x->cmd = ft_split(x->argv[t], ' ');
	while (x->paths[i] != NULL)
	{
		x->paths[i] = ft_strjoin(x->paths[i], "/");
		i++;
	}
	i = 0;
	while (x->paths[i] != NULL)
	{
		try = ft_strjoin(x->paths[i], x->cmd[0]);
		if (access(try, F_OK | X_OK) == 0)
			return (try);
		free(try);
		i++;
	}
	return (x->cmd[0]);
}

void	execve_exe(t_list *x)
{
	if (x->id1 == 0)
	{
		close(x->fd[0]);
		if (dup2(x->fd_a, 0) == -1)
			ft_exit("Dup2 Error");
		if (dup2(x->fd[1], 1) == -1)
			ft_exit("Dup2 Error");
		execve(x->path1, x->cmd1, x->env);
		ft_exit("Execve Error");
	}
	x->id2 = fork();
	if (x->id2 == -1)
		ft_exit("Fork Error");
	if (x->id2 == 0)
	{
		close(x->fd[1]);
		if (dup2(x->fd_b, 1) == -1)
			ft_exit("Dup2 Error");
		if (dup2(x->fd[0], 0) == -1)
			ft_exit("Dup2 Error");
		execve(x->path2, x->cmd2, NULL);
		ft_exit("Execve Error");
	}
}

void	pipex(t_list *x)
{
	x->path1 = get_path(x, 2);
	x->path2 = get_path(x, 3);
	x->cmd_args1 = cmd_arguments(x->argv, 2);
	x->cmd_args2 = cmd_arguments(x->argv, 3);
	x->cmd1 = (char *const []){x->path1, *x->cmd_args1, NULL};
	x->cmd2 = (char *const []){x->path2, *x->cmd_args2, NULL};
	if (pipe(x->fd) == -1)
		ft_exit("Pipe Error");
	x->id1 = fork();
	if (x->id1 == -1)
		ft_exit("Fork Error");
	execve_exe(x);
}

int	main(int argc, char **argv, char **env)
{
	t_list	x;

	if (argc != 5)
		exit(EXIT_FAILURE);
	x.fd_a = open(argv[1], O_CREAT | O_RDWR, 0666);
	x.fd_b = open(argv[4], O_CREAT | O_RDWR, 0666);
	if (x.fd_a == -1 || x.fd_b == -1)
		ft_exit("Open Error");
	x.argv = argv;
	x.env = env;
	pipex(&x);
	return (0);
}
