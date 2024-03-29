/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achraiti <achraiti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 13:44:26 by achraiti          #+#    #+#             */
/*   Updated: 2024/03/21 02:09:06 by achraiti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bonus.h"

void	here_doc_m(t_bonus *x)
{
	char	*line;

	x->fd_b = open(x->argv[x->argc - 1], O_CREAT | O_RDWR | O_APPEND, 0644);
	if (x->fd_b == -1)
		ft_exit("Open error");
	if (pipe(x->fd1) == -1)
		ft_exit("Pipe error");
	write(1, "pipe heredoc> ", 15);
	line = get_next_line(0);
	while (1 && line != NULL)
	{
		if (ft_strncmp(line, x->argv[2], ft_strlen(x->argv[2])) == 0
			&& ft_strlen(line) - 1 == ft_strlen(x->argv[2]))
		{
			free(line);
			break ;
		}
		write(1, "pipe heredoc> ", 15);
		write(x->fd1[1], line, ft_strlen(line));
		free(line);
		line = get_next_line(0);
	}
	her_doc(x);
}

int	ft_wait(t_bonus *x)
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

int	wait_(t_bonus *x)
{
	int	status;
	int	flag;

	flag = 0;
	if (waitpid(x->id1, &status, 0) > 0)
	{
		if (WEXITSTATUS(status))
			flag = 1;
	}
	while (wait(NULL) > 0)
		;
	if (flag)
		return (WEXITSTATUS(status));
	return (0);
}

void	inisilaze(t_bonus *x, char **argv, char **env, int argc)
{
	x->argv = argv;
	x->env = env;
	x->argc = argc;
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
		return (ft_wait(&x));
	}
	else
	{
		x.fd_a = open(argv[1], O_RDONLY);
		x.fd_b = open(argv[argc - 1], O_CREAT | O_WRONLY | O_TRUNC, 0644);
		if (x.fd_a == -1 || x.fd_b == -1)
			perror("open");
		pipex_bonus(&x);
		close(x.fd_a);
		close(x.fd_b);
	}
	return (wait_(&x));
}
