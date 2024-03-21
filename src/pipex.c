/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achraiti <achraiti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/28 15:20:41 by achraiti          #+#    #+#             */
/*   Updated: 2024/03/21 00:55:00 by achraiti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	second_child(t_list *x)
{
	close(x->fd[1]);
	if (dup2(x->fd_b, 1) == -1)
		ft_exit("Dup2 Error");
	if (dup2(x->fd[0], 0) == -1)
		ft_exit("Dup2 Error");
	close(x->fd[0]);
	execve(path(x, 3), flags(x->argv, 3, path(x, 3)), x->env);
	ft_exit("Execve Error");
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
		close(x->fd[1]);
		execve(path(x, 2), flags(x->argv, 2, path(x, 2)), x->env);
		ft_exit("Execve Error");
	}
	x->id2 = fork();
	if (x->id2 == -1)
		ft_exit("Fork Error");
	if (x->id2 == 0)
	{
		second_child(x);
	}
}

void	pipex(t_list *x)
{
	if (pipe(x->fd) == -1)
		ft_exit("Pipe Error");
	x->id1 = fork();
	if (x->id1 == -1)
		ft_exit("Fork Error");
	execve_exe(x);
	close(x->fd[0]);
	close(x->fd[1]);
}

int	ft_wait(t_list *x)
{
	int	status;
	int	flag;

	flag = 0;
	if (waitpid(x->id2, &status, 0) > 0)
	{
		if (WIFEXITED(status))
			flag = 1;
	}
	while (wait(NULL) > 0)
		;
	if (flag)
		return (WEXITSTATUS(status));
	return (0);
}

int	main(int argc, char **argv, char **env)
{
	t_list	x;

	if (argc != 5)
		exit(EXIT_FAILURE);
	x.argv = argv;
	x.env = env;
	x.fd_a = open(argv[1], O_RDONLY);
	x.fd_b = open(argv[4], O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (x.fd_a == -1)
		perror("open");
	if (x.fd_b == -1)
		perror("open");
	pipex(&x);
	return (ft_wait(&x));
}
