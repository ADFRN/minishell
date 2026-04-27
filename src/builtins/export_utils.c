/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afournie <afournie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/27 12:19:05 by afournie          #+#    #+#             */
/*   Updated: 2026/04/27 12:39:08 by afournie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	create_var(t_env **env, char *key, char *value)
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

int	is_valid_args(char *s)
{
	int	i;

	if (!s || !s[0])
		return (false);
	i = 0;
	if (!ft_isalpha(s[i]) && s[i] != '_')
		return (false);
	i++;
	while (s[i] && s[i] != '=')
	{
		if (!ft_isalnum(s[i]) && s[i] != '_')
			return (false);
		i++;
	}
	return (true);
}

bool	parse_kv(char *s, char **key, char **value, char **sep)
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

bool	update_var(t_env *env, char *key, char *value, char *sep)
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
