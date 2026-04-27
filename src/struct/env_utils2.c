/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttiprez <ttiprez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/24 15:54:54 by ttiprez           #+#    #+#             */
/*   Updated: 2026/04/27 11:50:27 by ttiprez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	env_size(t_env *env)
{
	int	i;

	i = 0;
	while (env)
	{
		i++;
		env = env->next;
	}
	return (i);
}

static t_env	*add_node(char *key, char *value)
{
	t_env	*node;

	if (!key || !value)
		return (free(key), free(value), NULL);
	node = ft_env_new();
	if (!node)
		return (free(key), free(value), NULL);
	node->key = key;
	node->value = value;
	return (node);
}

static t_env	*minimum_env(void)
{
	t_env	*head;
	t_env	*node;

	head = NULL;
	node = add_node(ft_strdup_classic("PWD"), getcwd(NULL, 0));
	if (!node)
		return (ft_env_free(&head), NULL);
	ft_env_add_back(&head, node);
	node = add_node(ft_strdup_classic("SHLVL"), ft_strdup_classic("1"));
	if (!node)
		return (ft_env_free(&head), NULL);
	ft_env_add_back(&head, node);
	node = add_node(ft_strdup_classic("_"), ft_strdup_classic("/usr/bin/env"));
	if (!node)
		return (ft_env_free(&head), NULL);
	ft_env_add_back(&head, node);
	return (head);
}

t_env	*init_env(char **envp)
{
	t_env	*head;
	t_env	*new_node;
	char	*separator;
	int		i;

	free((head = NULL, i = 0, NULL));
	if (!envp || !envp[0])
		return (minimum_env());
	while (envp && envp[i])
	{
		separator = ft_strchr(envp[i], '=');
		if (separator)
		{
			new_node = ft_env_new();
			if (!new_node)
				return (ft_env_free(&head), NULL);
			new_node->key = ft_substr_classic(envp[i], 0, separator - envp[i]);
			new_node->value = ft_strdup_classic(separator + 1);
			if (!new_node->key || !new_node->value)
				return (ft_env_free(&head), NULL);
			ft_env_add_back(&head, new_node);
		}
		i++;
	}
	return (head);
}

char	**env_to_char_tab(t_env *env)
{
	char	**env_tab;
	char	*tmp;
	int		i;

	env_tab = malloc(sizeof(char *) * (env_size(env) + 1));
	if (!env_tab)
		return (NULL);
	i = 0;
	while (env)
	{
		tmp = ft_strjoin(env->key, "=");
		if (!tmp)
			return (free_split(env_tab), NULL);
		env_tab[i] = ft_strjoin(tmp, env->value);
		free(tmp);
		if (!env_tab[i])
			return (free_split(env_tab), NULL);
		env = env->next;
		i++;
	}
	env_tab[i] = NULL;
	return (env_tab);
}
