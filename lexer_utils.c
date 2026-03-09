/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afournie <afournie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/06 15:02:53 by ttiprez           #+#    #+#             */
/*   Updated: 2026/03/09 11:14:03 by afournie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/header.h"

bool	have_valid_quotes(char *str)
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

void	free_split(char **splitted_words)
{
	int	i;

	i = -1;
	while (splitted_words[++i])
		free(splitted_words[i]);
	free(splitted_words);
}

void	print_split(char **splitted_words)
{
	int	i;

	i = -1;
	while (splitted_words[++i])
		printf("mot %d : %s\n", i, splitted_words[i]);
}
