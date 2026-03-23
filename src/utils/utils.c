/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttiprez <ttiprez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/12 13:43:16 by ttiprez           #+#    #+#             */
/*   Updated: 2026/03/23 10:54:40 by ttiprez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_pathlen(char *str)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != ' ' && str[i] != '"' && str[i] != '\'')
		i++;
	return (i);
}

void	free_split(char **splitted_words)
{
	int	i;

	i = -1;
	while (splitted_words[++i])
		free(splitted_words[i]);
	free(splitted_words);
}

static char	*add_equal(char *to_find)
{
	char	*str;

	str = ft_strjoin(to_find, "=");
	if (!str)
		return (NULL);
	return (str);
}

char	*get_envp(char **envp, char *to_find)
{
	int		i;
	int		len_str;
	char	*str;

	i = -1;
	str = add_equal(to_find);
	len_str = ft_pathlen(str);
	while (envp[++i])
		if (ft_strncmp(envp[i], str, len_str) == 0)
			return (&envp[i][len_str]);
	return ("");
}

int	get_env_i(char **envcpy, char *s)
{
	int	i;

	i = -1;
	while (envcpy[++i])
		if (ft_strncmp(envcpy[i], s, ft_strlen(s)) == 0)
			return (i);
	return (-1);
}
