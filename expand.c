/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttiprez <ttiprez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/06 15:29:44 by ttiprez           #+#    #+#             */
/*   Updated: 2026/03/09 12:24:16 by ttiprez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <header.h>

#include <stdio.h>

char	*get_envp(char **envp, char *to_find)
{
	int	i;

	i = -1;
	while (envp[++i])
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
			return (&envp[i][5]);
	return (NULL);
}

static int	ft_pathlen(char *str)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != ' ' && str[i] != '"' && str[i] != '\'')
		i++;
	return (i);
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
				expand_token($tokens[i], get_envp());
			}
		}
	}
}
