/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttiprez <ttiprez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/27 19:39:13 by ttiprez           #+#    #+#             */
/*   Updated: 2026/04/27 19:39:23 by ttiprez          ###   ########.fr       */
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
