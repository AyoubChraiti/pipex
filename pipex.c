/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achraiti <achraiti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/28 15:20:41 by achraiti          #+#    #+#             */
/*   Updated: 2024/02/15 22:37:09 by achraiti         ###   ########.fr       */
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

char *cmd_arguments(char **argv, int t)
{
	int count = 0;
	char **sp = ft_split(argv[t], ' ');
	char *res = NULL;
	char *tmp = NULL;
	int i = 1;
	while(sp[count] != NULL)
		count++;
	if(count == 1)
		return (NULL);
	while(sp[i])
	{
		tmp = ft_strjoin(sp[i], " ");
		res = ft_strjoin(res, tmp);
		i++;
	}
	return (res);
}

char    *get_path_cmd(char **argv, char **env, int t)
{
	int flag = 1;
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
	printf("%d\n", flag);
	if(flag)
		return (try);
	return (cmd1[0]);
}

void    pipex(int fd_a, int fd_b, char **argv, char **env)
{
    int     fd[2];
	pid_t   id1;
    pid_t   id2;

    pipe(fd);
    id1 = fork();
	if(id1 == 0)
	{
        close(fd[0]);
        dup2(fd_a, 0);
        dup2(fd[1], 1);
		char *const x[] = {"/bin/ls", "-l", "-a", NULL};
		execve("/bin/ls", x, env);
        perror("Error");
        exit(1);
	}
    id2 = fork();
    if(id2 == 0)
    {
        close(fd[1]);
        dup2(fd_b, 1);
        dup2(fd[0], 0);
        char *const c[] = {"/usr/bin/grep", "a", NULL};
        execve("/usr/bin/grep", c, NULL);
        perror("Error");
        exit(1);
    }
}

int main(int argc, char **argv, char **env)
{
	int		fd_a;
	int		fd_b;

	fd_a = open(argv[1], O_CREAT | O_RDWR);
	fd_b = open(argv[4], O_CREAT | O_RDWR);
    if(fd_a == -1 || fd_b == -1)
        perror("Files Error");
	pipex(fd_a, fd_b, argv, env);
	// char *res = get_path_cmd(argv, env, 2);
	// printf("%s\n", res);
	// char *x = cmd_arguments(argv, 2);
	// printf("%s\n", x);
    return 0;
}
