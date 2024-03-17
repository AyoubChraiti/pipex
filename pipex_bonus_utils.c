/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achraiti <achraiti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 18:30:46 by achraiti          #+#    #+#             */
/*   Updated: 2024/03/17 02:43:52 by achraiti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*get_path_b(t_bonus *x, int t)
{
	char	*try;
	int		i;

	i = 0;
	x->cmd = ft_split(x->argv[t], ' ');
	if (x->cmd[0] == NULL)
		return (NULL);
	if (access(x->cmd[0], F_OK | X_OK) == 0)
		return (x->cmd[0]);
	if (x->cmd[0][0] == '.' || x->cmd[0][0] == '/')
		return (ft_free(x->cmd, 0), NULL);
	x->paths = get_path_helper_b(x);
	while (x->paths && x->paths[i] != NULL)
	{
		try = ft_strjoin(x->paths[i], x->cmd[0]);
		if (access(try, F_OK | X_OK) == 0)
			return (ft_free(x->paths, 0), ft_free(x->cmd, 0), try);
		free(try);
		i++;
	}
	return (ft_free(x->paths, 0), ft_free(x->cmd, 0), NULL);
}

char	**get_path_helper_b(t_bonus *x)
{
	char	*tmp;
	char	**s;
	int		i;

	i = 0;
	tmp = NULL;
	s = ft_split(get_env(x->env), ':');
	while (s && s[i] != NULL)
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
	if (!env)
		return (NULL);
	while (env[i])
	{
		if (ft_strncmp(env[i], "PATH=", 5) == 0)
			return (env[i] + 5);
		i++;
	}
	return (NULL);
}
