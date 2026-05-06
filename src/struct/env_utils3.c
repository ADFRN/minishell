/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afournie <afournie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/24 18:28:50 by ttiprez           #+#    #+#             */
/*   Updated: 2026/05/04 16:46:25 by afournie         ###   ########.fr       */
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
		return (NULL);
	return (NULL);
}

static void	ft_env_update_two(t_env *new, t_env **env, char *key, char *value)
{
	if (!new)
		exit((cleaning(env), EXIT_FAILURE));
	new->key = ft_strdup_classic(key);
	new->value = ft_strdup_classic(value);
	if (!new->key || !new->value)
		exit((free(new->key), free(new->value), free(new), cleaning(env),
				EXIT_FAILURE));
	ft_env_add_back(env, new);
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
			if (!value)
			{
				curr->value = NULL;
				return ;
			}
			curr->value = ft_strdup_classic(value);
			if (!curr->value)
				exit((cleaning(env), EXIT_FAILURE));
			return ;
		}
		curr = curr->next;
	}
	new = ft_env_new();
	ft_env_update_two(new, env, key, value);
}
