/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achraiti <achraiti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/28 15:20:41 by achraiti          #+#    #+#             */
/*   Updated: 2024/02/14 15:08:58 by achraiti         ###   ########.fr       */
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
	
    pipe(fd);
    id1 = fork();
	if(id1 == 0)
	{
        close(fd[0]);
        dup2(fd_a, 0);
        dup2(fd[1], 1);
		char *const x[] = {"/bin/ls", "-l", NULL};
		execve("/bin/ls", x, env);
        write(2, "error in execve\n", 17);
        exit(1);
	}
    id2 = fork();
    if(id2 == 0)
    {
        close(fd[1]);
        dup2(fd_b, 1);
        dup2(fd[0], 0);
        char *const c[] = {"/usr/bin/grep", "p", NULL};
        execve("/usr/bin/grep", c, NULL);
        printf("Error executing grep\n");
        exit(1);
    }
    return 0;
}