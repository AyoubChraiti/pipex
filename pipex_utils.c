/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achraiti <achraiti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 14:28:46 by achraiti          #+#    #+#             */
/*   Updated: 2024/02/19 14:02:01 by achraiti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_free(char **s, int f)
{
	int i;
	if (f)
		i = 1;
	else
		i = 0;
	while (s[i])
		free(s[i++]);
	free(s);
}

char	*get_path(t_list *x, int t)
{
	char	*try;
	char	*tmp;
	int		i;

	i = 0;
	x->path_var = get_env(x->env);
	x->paths = ft_split(x->path_var, ':');
	x->cmd = ft_split(x->argv[t], ' ');
	while (x->paths[i] != NULL)
	{
		tmp = ft_strjoin(x->paths[i], "/");
		free(x->paths[i]);
		x->paths[i] = tmp;
		i++;
	}
	i = 0;
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
	return (sp);
}

void	ft_exit(char *err_msg)
{
	perror(err_msg);
	exit(EXIT_FAILURE);
}
