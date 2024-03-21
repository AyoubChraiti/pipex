/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achraiti <achraiti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 14:28:46 by achraiti          #+#    #+#             */
/*   Updated: 2024/03/21 01:02:50 by achraiti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

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

char	*path(t_list *x, int index)
{
	char	**paths;
	char	**args;
	char	*rs;
	int		i;

	i = 0;
	args = ft_split(x->argv[index], ' ');
	if (!args || !args[0])
		return (ft_free(args), NULL);
	if (access(args[0], F_OK | X_OK) == 0)
		return (args[0]);
	if (args[0][0] == '.' || args[0][0] == '/')
		return (ft_free(args), NULL);
	paths = path_helper(x);
	if (!paths)
		return (NULL);
	while (paths[i])
	{
		rs = ft_strjoin(paths[i], args[0]);
		if (access(rs, X_OK | F_OK) == 0)
			return (ft_free(paths), ft_free(args), rs);
		free(rs);
		i++;
	}
	return (ft_free(paths), ft_free(args), NULL);
}

char	**path_helper(t_list *x)
{
	int		i;
	char	*tmp;
	char	**rs;

	i = 0;
	rs = ft_split(get_env(x->env), ':');
	if (!rs)
		return (NULL);
	while (rs[i])
	{
		tmp = ft_strjoin(rs[i], "/");
		free(rs[i]);
		rs[i] = tmp;
		i++;
	}
	return (rs);
}

