/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achraiti <achraiti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 15:45:32 by achraiti          #+#    #+#             */
/*   Updated: 2024/03/19 20:38:49 by achraiti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_free(char **s, int f)
{
	int	i;

	if (!s)
		return ;
	if (f)
		i = 1;
	else
		i = 0;
	while (s[i])
		free(s[i++]);
	free(s);
}

int	only_spaces(char *s)
{
	int i = 0;
	int f = 0;

	while(s[i])
	{
		if (s[i] == ' ')
			f++;
		i++;
	}
	if (f == i)
		return (1);
	return (0);
}

char	**cmd_arguments(char **argv, int t, char *if_null)
{
	char	**sp;

	if (!if_null)
		return (NULL);
	if (ft_strlen (argv[t]) == 0 || only_spaces(argv[t]) == 1)
		return (NULL);
	sp = ft_split(argv[t], ' ');
	return (sp);
}

void	ft_exit(char *err_msg)
{
	perror(err_msg);
	exit(EXIT_FAILURE);
}

void	ft_exit_b(char *err_msg, t_bonus *x)
{
	perror(err_msg);
	free(x->arr);
	exit(EXIT_FAILURE);
}
