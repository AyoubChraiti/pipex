/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achraiti <achraiti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/28 15:20:41 by achraiti          #+#    #+#             */
/*   Updated: 2024/02/13 17:36:21 by achraiti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int main(int argc, char **argv, char **env)
{
	int     fd[2];
	pid_t   id1;
    pid_t   id2;
	int		fd_a;
	int		fd_b;

	fd_a = open(argv[1], O_CREAT | O_RDWR);
	fd_b = open(argv[4], O_CREAT | O_RDWR);
    if(fd_a == -1 || fd_b == -1)
        printf("error opening the files\n");
	
    if(dup2(fd_a, 0) == -1)
        printf("error in 2nd dup\n");
	if(dup2(fd_b, 1) == -1)
        printf("error in dup\n");
    
	id1 = fork();
    pipe(fd);
    dup2(fd_b, fd[1]);
	if(id1 == 0)
	{
		char *const x[] = {"/usr/bin/cat", NULL};
		execve("/usr/bin/cat", x, env);
        exit(EXIT_FAILURE);
	}
    else
    {
        id2 = fork();
        dup2(fd[0], 0);
        if(id2 == 0)
        {
            char *const p[] = {"/usr/bin/grep", "a", NULL};
            execve("/usr/bin/grep", p, env);
        }
        wait(NULL);
        // char x[1000];
        // read(fd[0], x, sizeof(x));
        // printf("%s\n", x);
    }
    return 0;
}