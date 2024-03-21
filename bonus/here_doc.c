/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achraiti <achraiti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 14:44:15 by achraiti          #+#    #+#             */
/*   Updated: 2024/03/21 02:10:01 by achraiti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bonus.h"

void	norm_func(t_bonus *x)
{
	if (pipe(x->fd2) == -1)
		ft_exit("Pipe error");
	x->id1 = fork();
	if (x->id1 == -1)
		ft_exit("Fork error");
	if (x->id1 == 0)
	{
		close(x->fd2[0]);
		close(x->fd1[1]);
		if (dup2(x->fd1[0], 0) == -1)
			ft_exit("Dup error");
		close(x->fd1[0]);
		if (dup2(x->fd2[1], 1) == -1)
			ft_exit("Dup error");
		close(x->fd2[0]);
		execve(path(x, 4), flags(x->argv, 4, path(x, 3)), x->env);
		ft_exit("Execve Error");
	}
	close(x->fd1[0]);
	close(x->fd1[1]);
}

void	her_doc(t_bonus *x)
{
	norm_func(x);
	x->id2 = fork();
	if (x->id2 == -1)
		ft_exit("Fork Error");
	if (x->id2 == 0)
	{
		close(x->fd2[1]);
		if (dup2(x->fd2[0], 0) == -1)
			ft_exit("Dup Error");
		if (dup2(x->fd_b, 1) == -1)
			ft_exit("Dup Error");
		execve(path(x, 4), flags(x->argv, 4, path(x, 3)), x->env);
		ft_exit("Execve Error");
	}
	close(x->fd2[0]);
	close(x->fd2[1]);
}
