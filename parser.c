/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttiprez <ttiprez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/10 15:28:54 by ttiprez           #+#    #+#             */
/*   Updated: 2026/02/12 14:02:47 by ttiprez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

int	count_words(char *str)
{
	int	i;
	int	j;
	int	nb_words;

	nb_words = 0;
	i = -1;
	while (str[++i])
	{
		if (str[i] == '"' && str[i] != '\\')
		{
			j = i;
			while (str[++j])
				if (str[j] == '"' && str[j - 1] != '\\')
					i = j;
		}
		else if (str[i] == '\'' && str[i] != '\\')
		{
			j = i;
			while (str[++j])
				if (str[j] == '\'' && str[j - 1] != '\\')
					i = j;
		}
		if (((str[i + 1] == ' ' || !str[i + 1]) && str[i] != ' '))
			nb_words++;
	}
	return (nb_words);
}

char	**split_words(char *rl)
{
	int		i;
	char	**splitted_words;

	splitted_words = malloc(sizeof(char *) * count_words(rl));
	if (!splitted_words)
		return (NULL);
	i = -1;
	while (rl[++i])
	{
		continue;
	}
}

void	print_each_words(char *rl)
{
	char **splitted_words;

	splitted_words = split_words(rl);
}