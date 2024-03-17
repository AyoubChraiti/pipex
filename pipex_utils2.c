/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achraiti <achraiti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 15:45:32 by achraiti          #+#    #+#             */
/*   Updated: 2024/03/17 02:01:19 by achraiti         ###   ########.fr       */
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

char	**cmd_arguments(char **argv, int t, char *if_null)
{
	char	**sp;

	if (!if_null)
		return (NULL);
	sp = ft_split(argv[t], ' ');
	return (sp);
}

void	ft_exit(char *err_msg)
{
	perror(err_msg);
	exit(EXIT_FAILURE);
}
