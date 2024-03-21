/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achraiti <achraiti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/28 15:20:39 by achraiti          #+#    #+#             */
/*   Updated: 2024/03/21 02:08:44 by achraiti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BONUS_H
# define BONUS_H

# include <stdio.h>
# include <errno.h>
# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <sys/wait.h>
# include <fcntl.h>
# include "../libft/libft.h"

typedef struct s_bonus
{
	int			fd1[2];
	int			fd2[2];
	int			fd_doc;
	int			fd_out;
	pid_t		id1;
	pid_t		id2;
	int			fd_a;
	int			fd_b;
	char		**argv;
	char		**env;
	int			argc;
	int			var;
	int			i;
}			t_bonus;

char	*get_env(char **env);
char	**flags(char **argv, int t, char *if_null);
void	ft_free(char **s);
char	*path(t_bonus *x, int t);
char	**path_helper(t_bonus *x);
void	pipex_bonus(t_bonus *x);
void	exec_first(t_bonus *x);
void	exec_midles(t_bonus *x);
void	exec_last(t_bonus *x);
void	her_doc(t_bonus *x);
void	here_doc_m(t_bonus *x);
void	ft_exit(char *err_msg);

#endif