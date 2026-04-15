/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afournie <afournie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/06 14:49:15 by afournie          #+#    #+#             */
/*   Updated: 2026/04/15 15:42:54 by afournie         ###   ########.fr       */
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

char	**env_cpy(char **envp)
{
	char	**cpy;
	int		size;
	int		i;

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

void	realloc_env(char ***env_ptr, char *new_var)
{
	char	**new_env;
	char	**old_env;
	int		i;
	int		size;

	old_env = *env_ptr;
	size = count_env_vars(old_env);
	new_env = malloc(sizeof(char *) * (size + 2));
	if (!new_env)
		return ;
	i = 0;
	while (i < size)
	{
		new_env[i] = old_env[i];
		i++;
	}
	new_env[i] = ft_strdup_classic(new_var);
	new_env[i + 1] = NULL;
	free(old_env);
	*env_ptr = new_env;
}
