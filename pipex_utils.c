/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achraiti <achraiti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 14:28:46 by achraiti          #+#    #+#             */
/*   Updated: 2024/02/16 20:52:55 by achraiti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*get_env(char **env)
{
	int	i;

	i = 0;
	while (env[i])
	{
		if (ft_strncmp(env[i], "PATH=", 5) == 0)
			return (env[i] + 5);
		i++;
	}
	return (NULL);
}

char	**cmd_arguments(char **argv, int t)
{
	char	**sp;

	sp = ft_split(argv[t], ' ');
	return (sp + 1);
}

void	ft_exit(char *err_msg)
{
	perror(err_msg);
	exit(EXIT_FAILURE);
}
