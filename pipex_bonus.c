/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achraiti <achraiti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 13:44:26 by achraiti          #+#    #+#             */
/*   Updated: 2024/02/29 14:14:34 by achraiti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	here_doc_m(t_bonus *x)
{
	char	*line;

	x->fd_b = open(x->argv[x->argc - 1], O_CREAT | O_RDWR, 0777);
	if (x->fd_b == -1)
		ft_exit("Open error");
	if (pipe(x->fd1) == -1)
		ft_exit("Pipe error");
	line = get_next_line(0);
	while (1)
	{
		if (ft_strncmp(line, x->argv[2], ft_strlen(x->argv[2])) == 0)
			break ;
		write(x->fd1[1], line, ft_strlen(line));
		free(line);
		line = get_next_line(0);
	}
	her_doc(x);
}

int	main(int argc, char **argv, char **env)
{
	t_bonus	x;

	x.argv = argv;
	x.env = env;
	x.argc = argc;
	if (argc < 5)
		return (1);
	if (argc == 6 && ft_strncmp(argv[1], "here_doc", 8) == 0)
		here_doc_m(&x);
	else
	{
		x.fd_a = open(argv[1], O_CREAT | O_RDONLY, 0666);
		x.fd_b = open(argv[argc - 1], O_CREAT | O_WRONLY, 0666);
		if (x.fd_a == -1 || x.fd_b == -1)
			ft_exit("Open Error");
		x.var = argc - 5;
		x.i = 2;
		pipex_bonus(&x);
		close(x.fd_a);
		close(x.fd_b);
	}
	return (0);
}
