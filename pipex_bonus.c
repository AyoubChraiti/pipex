/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achraiti <achraiti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 13:41:00 by achraiti          #+#    #+#             */
/*   Updated: 2024/02/27 14:25:19 by achraiti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	exec_first(t_bonus *x)
{
	if (pipe(x->fd1) == -1)
		perror("Pipe Error");
	x->id1 = fork();
	if (x->id1 == -1)
		perror("Fork Error");
	if (x->id1 == 0)
	{
		close(x->fd1[0]);
		if (dup2(x->fd_a, 0) == -1)
			perror("Dup Error");
		dup2(x->fd1[1], 1);
		execve(get_path_b(x, x->i), ft_split(x->argv[x->i], ' '), x->env);
		perror("Execve Error");
	}
	x->read_end = x->fd1[0];
	x->i++;
}

void exec_midles(t_bonus *x)
{
    if (pipe(x->fd2) == -1)
        perror("Pipe Error");
    x->id1 = fork();
    if (x->id1 == -1)
        perror("Fork Error");
    if (x->id1 == 0)
    {
        close(x->fd1[1]);
        close(x->fd2[0]);
        if (dup2(x->read_end, 0) == -1)
            perror("Dup Error");
        if (dup2(x->fd2[1], 1) == -1)
			perror("Dup Error");
        execve(get_path_b(x, x->i), ft_split(x->argv[x->i], ' '), x->env);
        perror("Execve Error");
    }
    x->read_end = x->fd2[0];
    x->i++;
}

void	exec_last(t_bonus *x)
{
	x->id1 = fork();
	if (x->id1 == -1)
		perror("Fork Error");
	if (x->id1 == 0)
	{
		if (dup2(x->read_end, 0) == -1)
			perror("Dup Error hhhh");
		if (dup2(x->fd_b, 1) == -1)
			perror("Dup Error hhhh");
		execve(get_path_b(x, x->i), ft_split(x->argv[x->i], ' '), x->env);
		perror("Execve Error");
	}
	close(x->fd2[0]);
	close(x->fd2[1]);
}

void	pipex_bonus(t_bonus *x)
{
	exec_first(x);
	// while (x->var > 0)
	// {
		exec_midles(x);
// 		x->var--;
// 	}
// 	exec_last(x);
}

int	main(int argc, char **argv, char **env)
{
	t_bonus	x;

	x.fd_a = open(argv[1], O_CREAT | O_RDONLY, 0666);
	x.fd_b = open(argv[argc - 1], O_CREAT | O_WRONLY, 0666);
	if (x.fd_a == -1 || x.fd_b == -1)
		ft_exit("Open Error");
	x.argv = argv;
	x.env = env;
    x.var = argc - 5;
    x.i = 2;
	pipex_bonus(&x);
	close(x.fd_a);
	close(x.fd_b);
	close(x.read_end);
	return (0);
}
