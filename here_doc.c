/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achraiti <achraiti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 14:44:15 by achraiti          #+#    #+#             */
/*   Updated: 2024/02/27 15:53:19 by achraiti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void pipex1(int fd_out, int doc, t_bonus *x)
{
    int fd[2];
    if (pipe(fd) == -1)
        ft_exit("pipe error");
    int id = fork();
    if(id == -1)
        ft_exit("fork error");
    if(id == 0)
    {
        char buff[100];
        int r = read(doc, buff, sizeof(buff));
        printf("%d\n", r);
        printf("%s\n", buff);
        close(fd[0]);
        if (dup2(doc, 0) == -1)
            ft_exit("dup eror");
        // if (dup2(fd[1], 1) == -1)
        //     ft_exit("dup error");
        execve(get_path_b(x, 3), cmd_arguments(x->argv, 3), x->env);
        printf("error here in execve\n");
    }
    // int id2 = fork();
    // if(id2 == 0)
    // {
    //     close(fd[1]);
    //     dup2(fd[0], 0);
    //     dup2(fd_out, 1);
    //     execve(get_path_b(x, 4), cmd_arguments(x->argv, 4), x->env);
    //     printf("error here in execve\n");
    // }
}

int main(int argc, char **argv, char **env)
{
    int    fd_doc;
    int    fd_out;
    char    *line;
    t_bonus x;
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
    pipex1(fd_out, fd_doc, &x);
    return 0;
}