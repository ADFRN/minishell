/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttiprez <ttiprez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/15 11:55:47 by afournie          #+#    #+#             */
/*   Updated: 2026/04/24 18:00:17 by ttiprez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_export(t_env	*env)
{
	t_env	*curr;

	curr = env;
	while (curr)
	{
		if (!curr->value)
			printf("export %s\n", curr->key);
		else
			printf("export %s=%s\n", curr->key, curr->value);
		curr = curr->next;
	}
}

static bool	add_var(char *s, t_env **env)
{
	char	*separator;
	t_env	*new_node;

	separator = ft_strchr(s, '=');
	if (separator)
	new_node = ft_env_new();
	if (!new_node)
		return (NULL);
	if (separator)
	{
		new_node->key = ft_substr_classic(s, 0, separator - s);
		new_node->value = ft_strdup_classic(separator + 1);
	}
	else
	{
		new_node->key = ft_strdup_classic(s);
		new_node->value = NULL;
	}
	if (!new_node->key || !new_node->value)
		return (false);
	ft_env_add_back(env, new_node);
	return (true);
}

void	exec_export(t_cmd *cmd, t_env **env)
{
	int	i;

	if (cmd->args[1])
	{
		i = 0;
		while (cmd->args[++i])
			if (!add_var(cmd->args[i], env))
				exit((ft_free(), ft_env_free(env), EXIT_FAILURE));
	}
	else
		print_export(*env);
}
