/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_add_var.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttiprez <ttiprez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/27 20:04:48 by ttiprez           #+#    #+#             */
/*   Updated: 2026/04/27 20:07:41 by ttiprez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	parse_kv(char *s, char **key, char **value, char **sep)
{
	*sep = ft_strchr(s, '=');
	*key = NULL;
	*value = NULL;
	if (*sep)
	{
		*key = ft_substr_classic(s, 0, *sep - s);
		*value = ft_strdup_classic(*sep + 1);
		if (!*key || !*value)
			return (free(*key), free(*value), false);
	}
	else
	{
		*key = ft_strdup_classic(s);
		if (!*key)
			return (false);
	}
	return (true);
}

static t_env	*find_var(t_env *env, char *key)
{
	while (env)
	{
		if (ft_strcmp(env->key, key) == 0)
			return (env);
		env = env->next;
	}
	return (NULL);
}

static bool	update_var(t_env *env, char *key, char *value, char *sep)
{
	t_env	*node;

	node = find_var(env, key);
	if (!node)
		return (false);
	if (sep)
	{
		free(node->value);
		node->value = value;
	}
	else
		free(value);
	free(key);
	return (true);
}

static bool	create_var(t_env **env, char *key, char *value)
{
	t_env	*new_node;

	new_node = ft_env_new();
	if (!new_node)
		return (free(key), free(value), false);
	new_node->key = key;
	new_node->value = value;
	ft_env_add_back(env, new_node);
	return (true);
}

bool	export_add_var(char *s, t_env **env)
{
	char	*key;
	char	*value;
	char	*sep;

	if (!parse_kv(s, &key, &value, &sep))
		return (false);
	if (update_var(*env, key, value, sep))
		return (true);
	if (!create_var(env, key, value))
		return (false);
	return (true);
}
