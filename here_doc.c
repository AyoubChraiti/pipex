/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achraiti <achraiti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 14:44:15 by achraiti          #+#    #+#             */
/*   Updated: 2024/02/27 19:49:15 by achraiti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	here_doc(int fd_out, int doc, t_bonus *x)
{
	int	fd[2];
	int	id;
	int id2;

	if (pipe(fd) == -1)
		ft_exit("pipe error");
	id = fork();
	if(id == -1)
		ft_exit("fork error");
	if(id == 0)
	{
		close(fd[0]);
		if (dup2(doc, 0) == -1)
			ft_exit("dup eror");
		if (dup2(fd[1], 1) == -1)
			ft_exit("dup error");
		execve(get_path_b(x, 3), cmd_arguments(x->argv, 3), x->env);
		ft_exit("Error in Execve");
	}
	id2 = fork();
	if(id2 == 0)
	{
		close(fd[1]);
		dup2(fd[0], 0);
		dup2(fd_out, 1);
		execve(get_path_b(x, 4), cmd_arguments(x->argv, 4), x->env);
		ft_exit("Error in Execve");
	}
	close(fd[0]);
	close(fd[1]);
}

int main(int argc, char **argv, char **env)
{
	int		fd_doc;
	int		fd_out;
	char	*line;
	t_bonus	x;

	x.argv = argv;
	x.env = env;
	fd_doc = open("here_doc", O_CREAT | O_RDWR, 0666);
	fd_out = open(argv[argc - 1], O_CREAT | O_RDWR, 0666);
	if (fd_doc == -1 || fd_out == -1)
		ft_exit("Open error");
	line = get_next_line(0);
	while (1)
	{
		if (ft_strncmp(line, argv[2], ft_strlen(argv[2])) == 0)
			break ;
		write(fd_doc, line, ft_strlen(line));
		free(line);
		line = get_next_line(0);
	}
	here_doc(fd_out, fd_doc, &x);
	close(fd_doc);
	close(fd_out);
	unlink("here_doc");
	return 0;
}
