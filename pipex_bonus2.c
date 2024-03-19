/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achraiti <achraiti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 13:41:00 by achraiti          #+#    #+#             */
/*   Updated: 2024/03/19 20:29:38 by achraiti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	exec_first(t_bonus *x)
{
	if (pipe(x->fd1) == -1)
		ft_exit_b("Pipe Error", x);
	x->id1 = fork();
	if (x->id1 == -1)
		ft_exit_b("Fork Error", x);
	if (x->id1 == 0)
	{
		close(x->fd1[0]);
		if (dup2(x->fd_a, 0) == -1)
			ft_exit_b("Dup Error", x);
		if (dup2(x->fd1[1], 1) == -1)
			ft_exit_b("Dup Error", x);
		close(x->fd1[1]);
		execve(get_path_b(x, x->i),
			cmd_arguments(x->argv, x->i, get_path_b(x, x->i)), x->env);
		ft_exit_b("Execve Error", x);
	}
	dup2(x->fd1[0], 0);
	close(x->fd1[0]);
	close(x->fd1[1]);
	x->i++;
}

void	exec_midles(t_bonus *x)
{
	if (pipe(x->fd2) == -1)
		ft_exit_b("Pipe Error", x);
	x->id1 = fork();
	if (x->id1 == -1)
		ft_exit_b("Fork Error", x);
	if (x->id1 == 0)
	{
		close(x->fd2[0]);
		if (dup2(x->fd2[1], 1) == -1)
			ft_exit_b("Dup Error", x);
		close(x->fd2[1]);
		execve(get_path_b(x, x->i),
			cmd_arguments(x->argv, x->i, get_path_b(x, x->i)), x->env);
		ft_exit_b("Execve Error", x);
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
		ft_exit_b("Fork Error", x);
	x->arr[0] = x->id1;
	if (x->id1 == 0)
	{
		if (dup2(x->fd_b, 1) == -1)
			ft_exit_b("Dup Error", x);
		execve(get_path_b(x, x->i),
			cmd_arguments(x->argv, x->i, get_path_b(x, x->i)), x->env);
		ft_exit_b("Execve Error", x);
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
