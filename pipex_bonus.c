/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achraiti <achraiti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 13:44:26 by achraiti          #+#    #+#             */
/*   Updated: 2024/03/02 14:36:55 by achraiti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	here_doc_m(t_bonus *x)
{
	char	*line;

	x->fd_b = open(x->argv[x->argc - 1], O_CREAT | O_RDWR, 0644);
	if (x->fd_b == -1)
		ft_exit("Open error");
	if (pipe(x->fd1) == -1)
		ft_exit("Pipe error");
	write(0, "pipe heredoc> ", 15);
	line = get_next_line(0);
	while (1)
	{
		if (ft_strncmp(line, x->argv[2], ft_strlen(x->argv[2])) == 0
			&& ft_strlen(line) - 1 == ft_strlen(x->argv[2]))
			break ;
		write(0, "pipe heredoc> ", 15);
		write(x->fd1[1], line, ft_strlen(line));
		free(line);
		line = get_next_line(0);
	}
	her_doc(x);
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

int wait_(t_bonus *x)
{
	int res;
	int status;
	
	res = 0;
	while (x->ind > 0)
	{
		if (waitpid(x->arr[x->ind], &status, 0) == -1)
		if (WIFEXITED(status))
		{
			if (WEXITSTATUS(status))
			{
				res = WEXITSTATUS(status);
				break ;
			}
		}
		x->ind--;
	}
	return (res);
}

void	inisilaze(t_bonus *x, char **argv, char **env, int argc)
{
	x->argv = argv;
	x->env = env;
	x->argc = argc;
	x->arr = (int *)malloc(sizeof(int) * argc - 3);
	x->ind = 0;
	x->var = argc - 5;
	x->i = 2;
}

int	main(int argc, char **argv, char **env)
{
	t_bonus	x;

	inisilaze(&x, argv, env, argc);
	if (argc < 5)
		return (1);
	if (argc == 6 && ft_strncmp(argv[1], "here_doc", 8) == 0
		&& ft_strlen(argv[1]) == 8)
	{
		here_doc_m(&x);
		free(x.arr);
		return (ft_wait(&x));
	}
	else
	{
		x.fd_a = open(argv[1], O_RDONLY);
		x.fd_b = open(argv[argc - 1], O_CREAT | O_WRONLY | O_TRUNC, 0644);
		if (x.fd_a == -1 || x.fd_b == -1)
			ft_exit("Open Error");
		pipex_bonus(&x);
		close(x.fd_a);
		close(x.fd_b);
	}
	free(x.arr);
	return (wait_(&x));
}
