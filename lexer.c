/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttiprez <ttiprez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/10 15:28:54 by ttiprez           #+#    #+#             */
/*   Updated: 2026/03/05 14:03:22 by ttiprez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <header.h>

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

bool	check_quotes(char *str)
{
	int		i;
	t_state	state;

	state = DEFAULT;
	i = -1;
	while (str[++i])
	{
		if (state == DEFAULT)
		{
			if (str[i] == '\'')
				state = IN_SINGLE_QUOTE;
			else if (str[i] == '"')
				state = IN_DOUBLE_QUOTE;
		}
		else if (str[i] == '\'' && state == IN_SINGLE_QUOTE)
			state = DEFAULT;
		else if (str[i] == '"' && state == IN_DOUBLE_QUOTE)
			state = DEFAULT;
	}
	return (state == DEFAULT);
}

int	count_words(char *str)
{
	int		i;
	int		nb_words;
	t_state	state;

	state = DEFAULT;
	nb_words = 0;
	i = -1;
	while (str[++i])
	{
		if (state == DEFAULT)
		{
			if ((str[i + 1] == ' ' || !str[i + 1]) && (str[i] != ' '))
				nb_words++;	
		}
	}
	return (nb_words);
}

char	**lexer(char *rl)
{
	int		i;
	char	**splitted_words;

	splitted_words = malloc(sizeof(char *) * (count_words(rl) + 1));
	if (!splitted_words)
		return (NULL);
	i = -1;
	while (rl[++i])
	{
		continue ;
	}
	return (NULL);
}

void	print_each_words(char *rl)
{
	char	**splitted_words;

	splitted_words = lexer(rl);
}
