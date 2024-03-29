/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achraiti <achraiti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 13:41:00 by achraiti          #+#    #+#             */
/*   Updated: 2024/03/21 02:09:35 by achraiti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bonus.h"

void	exec_first(t_bonus *x)
{
	if (pipe(x->fd1) == -1)
		ft_exit("Pipe Error");
	x->id1 = fork();
	if (x->id1 == -1)
		ft_exit("Fork Error");
	if (x->id1 == 0)
	{
		close(x->fd1[0]);
		if (dup2(x->fd_a, 0) == -1)
			ft_exit("Dup Error");
		if (dup2(x->fd1[1], 1) == -1)
			ft_exit("Dup Error");
		close(x->fd1[1]);
		execve(path(x, x->i), flags(x->argv, x->i, path(x, x->i)), x->env);
		ft_exit("Execve Error");
	}
	dup2(x->fd1[0], 0);
	close(x->fd1[0]);
	close(x->fd1[1]);
	x->i++;
}

void	exec_midles(t_bonus *x)
{
	if (pipe(x->fd2) == -1)
		ft_exit("Pipe Error");
	x->id1 = fork();
	if (x->id1 == -1)
		ft_exit("Fork Error");
	if (x->id1 == 0)
	{
		close(x->fd2[0]);
		if (dup2(x->fd2[1], 1) == -1)
			ft_exit("Dup Error");
		close(x->fd2[1]);
		execve(path(x, x->i), flags(x->argv, x->i, path(x, x->i)), x->env);
		ft_exit("Execve Error");
	}
	dup2(x->fd2[0], 0);
	close(x->fd2[0]);
	close(x->fd2[1]);
	x->i++;
}

void	exec_last(t_bonus *x)
{
	x->id1 = fork();
	if (x->id1 == -1)
		ft_exit("Fork Error");
	if (x->id1 == 0)
	{
		if (dup2(x->fd_b, 1) == -1)
			ft_exit("Dup Error");
		execve(path(x, x->i), flags(x->argv, x->i, path(x, x->i)), x->env);
		ft_exit("Execve Error");
	}
	x->i++;
}

void	pipex_bonus(t_bonus *x)
{
	exec_first(x);
	while (x->var > 0)
	{
		exec_midles(x);
		x->var--;
	}
	exec_last(x);
	close(0);
}
