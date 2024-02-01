/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achraiti <achraiti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/28 15:20:41 by achraiti          #+#    #+#             */
/*   Updated: 2024/01/31 15:19:36 by achraiti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int main(int argc, char **argv, char **envp)
{
    (void) argc;
    (void) argv;
    (void) envp;
    int n;
    int i = fork();
    if(i == 0)
        n = 0;
    else
        n = 10;
    int k = 0;
    if(i != 0)
        wait(NULL);
    printf("i = %d\n", i);
    if(i != 0)
        k = 10;
    while(k <= 20)
        printf("k = %d\n", k++);
    printf("finished\n");
}
