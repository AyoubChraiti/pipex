/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achraiti <achraiti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/28 15:20:41 by achraiti          #+#    #+#             */
/*   Updated: 2024/02/16 14:27:21 by achraiti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*get_env(char **env)
{
	int i = 0;
	
	while(env[i])
	{
		if(ft_strncmp(env[i], "PATH=", 5) == 0)
			return (env[i] + 5);
		i++;
	}
	return (NULL);
}

char **cmd_arguments(char **argv, int t)
{
	char **sp = ft_split(argv[t], ' ');
	return (sp + 1);
}

char    *get_path(char **argv, char **env, int t)
{
	int flag = 0;
	char *try;
	char *path_var = get_env(env);
	char **paths = ft_split(path_var, ':');
	char **cmd1 = ft_split(argv[t], ' ');
	int i = 0;
	
	while(paths[i] != NULL)
	{
		paths[i] = ft_strjoin(paths[i], "/");
		i++;
	}
	i = 0;
	while(paths[i] != NULL)
	{
		try = ft_strjoin(paths[i], cmd1[0]);
		if(access(try, F_OK | X_OK) == 0)
		{
			flag = 1;
			break ;
		}
		free(try);
		i++;
	}
	if(flag)
		return (try);
	return (cmd1[0]);
}

void    pipex(int fd_a, int fd_b, char **argv, char **env)
{
    int     fd[2];
	pid_t   id1;
    pid_t   id2;
	char *path1 = get_path(argv, env, 2);
	char *path2 = get_path(argv, env, 3);
	char **cmd_args1 = cmd_arguments(argv, 2);
	char **cmd_args2 = cmd_arguments(argv, 3);
	char *const cmd1[] = {path1, *cmd_args1, NULL};
	char *const cmd2[] = {path2, *cmd_args2, NULL};

    pipe(fd);
    id1 = fork();
	if(id1 == 0)
	{
        close(fd[0]);
        dup2(fd_a, 0);
        dup2(fd[1], 1);
		execve(path1, cmd1, env);
        perror("Error");
        exit(1);
	}
    id2 = fork();
    if(id2 == 0)
    {
        close(fd[1]);
        dup2(fd_b, 1);
        dup2(fd[0], 0);
        execve(path2, cmd2, NULL);
        perror("Error");
        exit(1);
    }
}

int main(int argc, char **argv, char **env)
{
	if (argc != 5)
		exit(EXIT_FAILURE);
	int		fd_a;
	int		fd_b;

	fd_a = open(argv[1], O_CREAT | O_RDWR);
	fd_b = open(argv[4], O_CREAT | O_RDWR);
    if(fd_a == -1 || fd_b == -1)
	{
		perror("Files Error");
	}
	pipex(fd_a, fd_b, argv, env);
	// char *res = get_path(argv, env, 2);
	// printf("%s\n", res);
	// char **x = cmd_arguments(argv, 2);
	// for (int i = 0; x[i] != NULL; i++)
	// 	printf("%s\n", x[i]);
    return 0;
}
