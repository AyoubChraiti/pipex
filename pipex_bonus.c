/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achraiti <achraiti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 13:41:00 by achraiti          #+#    #+#             */
/*   Updated: 2024/02/24 14:09:23 by achraiti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	execve_1(t_bonus *x)
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
}


void    execve_last(t_bonus *x)
{
    if (x->id1 == 0)
	{
		close(x->fd[1]);
		if (dup2(x->fd_b, 1) == -1)
			ft_exit("Dup2 Error");
		if (dup2(x->fd[0], 0) == -1)
			ft_exit("Dup2 Error");
		execve(x->path1, x->cmd1, NULL);
		ft_exit("Execve Error");
	}
}

void    execve_mid(t_bonus *x, int fd[2])
{
    if (x->id1 == 0)
	{
		close(fd[1]);
        close(x->fd_mid[0]);
		if (dup2(x->fd_mid[1], 1) == -1)
			ft_exit("Dup2 Error");
		if (dup2(fd[0], 0) == -1)
			ft_exit("Dup2 Error");
		execve(x->path1, x->cmd1, NULL);
		ft_exit("Execve Error");
	}
}


void	pipex_bonus(t_bonus *x)
{
    x->flag = 0;
    x->path1 = get_path_b(x, x->i);
    x->cmd1 = cmd_arguments(x->argv, x->i);
    if (pipe(x->fd) == -1)
        ft_exit("Pipe Error");
    x->id1 = fork();
    if (x->id1 == -1)
        ft_exit("Fork Error");
    if (x->i == 2)
	{
        execve_1(x);
	}
	if (x->i == x->var)
        return (execve_last(x));
	printf("i-->%d var-->%d", x->i, x->var);
    while (x->var > 0)
    {
        x->i++;
        x->path1 = get_path_b(x, x->i);
        x->cmd1 = cmd_arguments(x->argv, x->i);
        if (pipe(x->fd_mid) == -1)
			ft_exit("Pipe Error");
        x->id1 = fork();
		if (x->id1 == -1)
        	ft_exit("Fork Error");
        execve_mid(x, x->fd);
        x->fd[0] = x->fd_mid[0];
        x->fd[1] = x->fd_mid[1];
		x->var--;
    }
    if (x->i == x->var)
        execve_last(x);
}

int	ft_wait(t_bonus *x)
{
	int	status1;
	int	status2;
	int	res;

	res = 0;
	waitpid(x->id1, &status1, 0);
	waitpid(x->id2, &status2, 0);
	if (WEXITSTATUS(status1) || WEXITSTATUS(status2))
		res = WEXITSTATUS(status1) + WEXITSTATUS(status2);
	return (res);
}

int	main(int argc, char **argv, char **env)
{
	t_bonus	x;
	int		exit_status;

	x.fd_a = open(argv[1], O_CREAT | O_RDONLY, 0666);
	x.fd_b = open(argv[argc - 1], O_CREAT | O_WRONLY, 0666);
	if (x.fd_a == -1 || x.fd_b == -1)
		ft_exit("Open Error");
	x.argv = argv;
	x.env = env;
    x.var = argc - 3;
    x.i = 2;
	pipex_bonus(&x);
	close(x.fd[0]);
	close(x.fd[1]);
	exit_status = ft_wait(&x);
	return (exit_status);
}
