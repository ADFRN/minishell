/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttiprez <ttiprez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/12 13:43:16 by ttiprez           #+#    #+#             */
/*   Updated: 2026/04/24 17:36:10 by ttiprez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*add_equal(char *to_find)
{
	char	*str;

	str = ft_strjoin(to_find, "=");
	if (!str)
		return (NULL);
	return (str);
}

char	*get_envp(t_env *env, char *key)
{
	t_env	*curr;

	curr = env;
	while (curr)
	{
		if (!ft_strcmp(curr->key, key))
			return (curr->value);
		curr = curr->next;
	}
	return ("");
}

void	free_split(char **splitted_words)
{
	int	i;

	i = -1;
	while (splitted_words[++i])
		free(splitted_words[i]);
	free(splitted_words);
}
