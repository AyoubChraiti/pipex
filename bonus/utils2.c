/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achraiti <achraiti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 15:45:32 by achraiti          #+#    #+#             */
/*   Updated: 2024/03/21 02:08:16 by achraiti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bonus.h"

void	ft_free(char **s)
{
	int	i;

	i = 0;
	while (s[i])
		free(s[i++]);
	free(s);
}

char	**flags(char **argv, int t, char *if_null)
{
	char	**flags;

	if (!if_null)
		return (NULL);
	flags = ft_split(argv[t], ' ');
	if (flags == NULL || !flags[0] || ft_strlen(flags[0]) == 0)
		return (NULL);
	return (flags);
}

void	ft_exit(char *err_msg)
{
	perror(err_msg);
	exit(EXIT_FAILURE);
}
