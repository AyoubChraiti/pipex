/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achraiti <achraiti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/28 15:20:41 by achraiti          #+#    #+#             */
/*   Updated: 2024/02/10 18:34:47 by achraiti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int main(int argc, char **argv, char **envp)
{
    (void)argc;
    (void)argv;
    (void)envp;
    char *env[] = { NULL };
    char *d[] = { "ls",  NULL };
    int x = fork();
    printf("%d\n", getgid());
    if(x == 0)
        execve("/usr/bin/ls", d, env);
    printf("%d\n", getgid());;
    return 1;
}
