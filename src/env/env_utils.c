/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttiprez <ttiprez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/06 14:49:15 by afournie          #+#    #+#             */
/*   Updated: 2026/04/20 15:23:48 by ttiprez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count_env_vars(char **envp)
{
	int	i;

	i = 0;
	while (envp && envp[i])
		i++;
	return (i);
}

void	free_env(char **env)
{
	int	i;

	i = 0;
	if (!env)
		return ;
	while (env[i])
	{
		free(env[i]);
		i++;
	}
	free(env);
}

static char	**init_env(void)
{
	char	**env;

	env = malloc(sizeof(char *) * 4);
	env[0] = ft_strjoin("PWD=", getcwd(NULL, 0));
	env[1] = ft_strdup("SHLVL=1");
	env[2] = ft_strdup("_=/usr/bin/env");
	env[3] = NULL;
	return (env);
}

char	**env_cpy(char **envp)
{
	char	**cpy;
	int		size;
	int		i;

	if (!envp[0])
		return (init_env());
	size = count_env_vars(envp);
	cpy = malloc(sizeof(char *) * (size + 1));
	if (!cpy)
		return (NULL);
	i = 0;
	while (i < size)
	{
		cpy[i] = ft_strdup_classic(envp[i]);
		if (!cpy[i])
		{
			free_env(cpy);
			return (NULL);
		}
		i++;
	}
	cpy[i] = NULL;
	return (cpy);
}
