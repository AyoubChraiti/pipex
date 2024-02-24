/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achraiti <achraiti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 15:02:23 by achraiti          #+#    #+#             */
/*   Updated: 2024/02/23 15:13:01 by achraiti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*get_path_b(t_bonus *x, int t)
{
	char	*try;
	int		i;

	i = 0;
	x->cmd = ft_split(x->argv[t], ' ');
	x->paths = get_path_helper_b(x);
	while (x->paths[i] != NULL)
	{
		try = ft_strjoin(x->paths[i], x->cmd[0]);
		if (access(try, F_OK | X_OK) == 0)
		{
			ft_free(x->paths, 0);
			ft_free(x->cmd, 0);
			return (try);
		}
		free(try);
		i++;
	}
	ft_free(x->paths, 0);
	ft_free(x->cmd, 1);
	return (x->cmd[0]);
}

char	**get_path_helper_b(t_bonus *x)
{
	char	*tmp;
	char	**s;
	int		i;

	i = 0;
	x->path_var = get_env(x->env);
	s = ft_split(x->path_var, ':');
	while (s[i] != NULL)
	{
		tmp = ft_strjoin(s[i], "/");
		free(s[i]);
		s[i] = tmp;
		i++;
	}
	return (s);
}

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