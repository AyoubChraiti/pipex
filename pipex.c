/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achraiti <achraiti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/28 15:20:41 by achraiti          #+#    #+#             */
/*   Updated: 2024/02/16 19:11:30 by achraiti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*get_env(char **env)
{
	int	i;

	i = 0;
	while (env[i])
	{
		if (ft_strncmp(env[i], "PATH=", 5) == 0)
			return (env[i] + 5);
		i++;
	}
	return (NULL);
}

char	**cmd_arguments(char **argv, int t)
{
	char	**sp;

	sp = ft_split(argv[t], ' ');
	return (sp + 1);
}

char	*get_path(t_list *x, int t)
{
	char	*try;
	int		i;

	i = 0;
	x->flag = 0;
	x->path_var = get_env(x->env);
	x->paths = ft_split(x->path_var, ':');
	x->cmd = ft_split(x->argv[t], ' ');
	while (x->paths[i] != NULL)
	{
		x->paths[i] = ft_strjoin(x->paths[i], "/");
		i++;
	}
	i = 0;
	while (x->paths[i] != NULL)
	{
		try = ft_strjoin(x->paths[i], x->cmd[0]);
		if (access(try, F_OK | X_OK) == 0)
		{
			x->flag = 1;
			break ;
		}
		free(try);
		i++;
	}
	if (x->flag)
		return (try);
	return (x->cmd[0]);
}

void	pipex(t_list *x)
{
	x->path1 = get_path(x, 2);
	x->path2 = get_path(x, 3);
	x->cmd_args1 = cmd_arguments(x->argv, 2);
	x->cmd_args2 = cmd_arguments(x->argv, 3);
	x->cmd1 = (char *const []){x->path1, *x->cmd_args1, NULL};
	x->cmd2 = (char *const []){x->path2, *x->cmd_args2, NULL};
	if (pipe(x->fd) == -1)
		perror("Pipe Error");
	x->id1 = fork();
	if (x->id1 == -1)
		perror("Fork Error");
	if (x->id1 == 0)
	{
		close(x->fd[0]);
		dup2(x->fd_a, 0);
		dup2(x->fd[1], 1);
		execve(x->path1, x->cmd1, x->env);
		perror("Execve Error");
	}
	x->id2 = fork();
	if (x->id2 == -1)
		perror("Fork Error");
	if (x->id2 == 0)
	{
		close(x->fd[1]);
		dup2(x->fd_b, 1);
		dup2(x->fd[0], 0);
		execve(x->path2, x->cmd2, NULL);
		perror("Execve Error");
	}
}

int	main(int argc, char **argv, char **env)
{
	t_list	x;

	if (argc != 5)
		exit(EXIT_FAILURE);
	x.fd_a = open(argv[1], O_CREAT | O_RDWR, 0666);
	x.fd_b = open(argv[4], O_CREAT | O_RDWR, 0666);
	if (x.fd_a == -1 || x.fd_b == -1)
	{
		perror("Open Error");
	}
	x.argv = argv;
	x.env = env;
	pipex(&x);
	return (0);
}
