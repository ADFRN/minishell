/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttiprez <ttiprez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/24 15:06:00 by ttiprez           #+#    #+#             */
/*   Updated: 2026/04/24 18:25:42 by ttiprez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	*ft_env_new(void)
{
	t_env	*env;

	env = malloc(sizeof(t_env));
	if (!env)
		return (NULL);
	env->key = NULL;
	env->value = NULL;
	env->prev = NULL;
	env->next = NULL;
	return (env);
}

void	ft_env_add_back(t_env **lst, t_env *new)
{
	t_env	*last;

	if (!*lst)
	{
		*lst = new;
		return ;
	}
	last = *lst;
	while (last->next)
		last = last->next;
	last->next = new;
	new->prev = last;
}
 
void	ft_env_remove(t_env **lst, char *key)
{
	t_env	*curr;

	if (!lst || !*lst)
		return ;
	curr = *lst;
	while (curr && (ft_strcmp(curr->key, key) != 0))
		curr = curr->next;
	if (!curr)
		return ;
	if (curr->prev)
		curr->prev->next = curr->next;
	else
		*lst = curr->next;
	if (curr->next)
		curr->next->prev = curr->prev;
	free(curr->key);
	free(curr->value);
	free(curr);
}

void	ft_env_free(t_env **lst)
{
	t_env	*curr;
	t_env	*next;

	curr = *lst;
	while (curr)
	{
		free(curr->key);
		free(curr->value);
		next = curr->next;
		free(curr);
		curr = next;
	}
	*lst = NULL;
}

t_env	*ft_env_get(t_env **env, char *key)
{
	t_env *curr;

	curr = *env;
	while (curr)
	{
		if (!ft_strcmp(curr->key, key))
			return (curr);
		curr = curr->next;
	}
	return (NULL);
}
