/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttiprez <ttiprez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/05 13:25:55 by afournie          #+#    #+#             */
/*   Updated: 2026/04/27 19:39:03 by ttiprez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exec_env(t_env	*env)
{
	t_env	*curr;

	curr = env;
	while (curr)
	{
		if (curr->key && curr->value)
		{
			ft_putstr(curr->key);
			ft_putstr("=");
			ft_putstr(curr->value);
			ft_putstr("\n");
		}
		curr = curr->next;
	}
	return (EXIT_SUCCESS);
}

char	*exec_pwd(void)
{
	char	tmp[PATH_MAX];
	char	*path;

	if (getcwd(tmp, PATH_MAX) != NULL)
	{
		path = ft_strdup(tmp);
		if (!path)
			return (NULL);
		return (path);
	}
	return (perror("minishell: pwd"), NULL);
}
