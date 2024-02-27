/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achraiti <achraiti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/28 15:20:39 by achraiti          #+#    #+#             */
/*   Updated: 2024/02/26 21:30:59 by achraiti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <sys/wait.h>
# include <fcntl.h>
# include "libft/libft.h"

typedef struct s_bonus
{
	int			fd1[2];
	int			fd2[2];
	int			read_end;
	pid_t		id1;
	int			fd_a;
	int			fd_b;
	char		**argv;
	char		**env;
	int			var;
	int			i;
	char		*path1;
	char		*path_var;
	char		**paths;
	char		**cmd;
	char		**cmd1;
}			t_bonus;

typedef struct s_list
{
	int			fd[2];
	pid_t		id1;
	pid_t		id2;
	int			fd_a;
	int			fd_b;
	char		**argv;
	char		**env;
	char		*path1;
	char		*path2;
	char		*path_var;
	char		**paths;
	char		**cmd;
	char		**cmd1;
	char		**cmd2;
}			t_list;

char	*get_env(char **env);
char	**cmd_arguments(char **argv, int t);
void	ft_exit(char *err_msg);
void	ft_free(char **s, int f);
char	*get_path(t_list *x, int t);
char	**get_path_helper(t_list *x);
char	*get_path_b(t_bonus *x, int t);
char	**get_path_helper_b(t_bonus *x);

#endif