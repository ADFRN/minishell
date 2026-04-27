/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttiprez <ttiprez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/24 18:28:50 by ttiprez           #+#    #+#             */
/*   Updated: 2026/04/27 11:51:09 by ttiprez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_env_get_val(t_env *env, char *key)
{
	while (env)
	{
		if (!ft_strcmp(env->key, key))
			return (env->value);
		env = env->next;
	}
	if (!ft_strcmp(key, "PATH"))
		return (DEFAULT_PATH);
	return (NULL);
}

void	ft_env_update(t_env **env, char *key, char *value)
{
	t_env	*curr;
	t_env	*new;

	curr = *env;
	while (curr)
	{
		if (!ft_strcmp(curr->key, key))
		{
			free(curr->value);
			curr->value = ft_strdup_classic(value);
			return ;
		}
		curr = curr->next;
	}
	new = ft_env_new();
	if (!new)
		exit((ft_free(), ft_env_free(env), EXIT_FAILURE));
	new->key = ft_strdup_classic(key);
	new->value = ft_strdup_classic(value);
	if (!new->key || !new->value)
		exit((free(new->key), free(new->value), free(new),
				ft_free(), ft_env_free(env), EXIT_FAILURE));
	ft_env_add_back(env, new);
}
