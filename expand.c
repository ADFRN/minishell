/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttiprez <ttiprez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/06 15:29:44 by ttiprez           #+#    #+#             */
/*   Updated: 2026/03/09 15:05:51 by ttiprez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/header.h"

#include <stdio.h>

static int	ft_pathlen(char *str)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != ' ' && str[i] != '"' && str[i] != '\'')
		i++;
	return (i);
}

static char	*add_equal(char *to_find)
{
	char *str;

	str = malloc(ft_stren(to_find) + 2);
	ft_strcpy(str, to_find);
	ft_strcat(str, "=");
	free(to_find);
	return (str);
}

char	*get_envp(char **envp, char *to_find)
{
	int		i;
	int		len_to_find;

	i = -1;
	to_find = add_equal(to_find);
	len_to_find = ft_pathlen(to_find);
	while (envp[++i])
		if (ft_strncmp(envp[i], to_find, len_to_find) == 0)
			return (free(to_find), &envp[i][len_to_find + 1]);
	return (NULL);
}

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
