/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttiprez <ttiprez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/06 15:29:44 by ttiprez           #+#    #+#             */
/*   Updated: 2026/03/09 15:36:11 by ttiprez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#include <stdio.h>

void	expand(char **tokens, char **envp)
{
	int		i;
	int		j;
	t_state	state;

	state = DEFAULT;
	i = -1;
	while (tokens[++i])
	{
		j = -1;
		while (tokens[i][++j])
		{
			set_state(tokens[i][j], &state);
			if (tokens[i][j] == '$' &&
				(state == DEFAULT || state == IN_DOUBLE_QUOTE))
			{
				j++;
				printf("ft_pathlen(%s) = %d\n", &tokens[i][j], ft_pathlen(&tokens[i][j]));
				printf("ENVP_VARIABLE = %s\n", get_envp(envp, &tokens[i][j]));
			}
		}
	}
}
