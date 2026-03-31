/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afournie <afournie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/06 15:02:53 by ttiprez           #+#    #+#             */
/*   Updated: 2026/03/31 13:52:52 by afournie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

bool	is_metachar(char c)
{
	return (c == '|' || c == '<' || c == '>');
}

int	get_operator_len(char *str)
{
	if ((str[0] == '<' && str[1] == '<') || (str[0] == '>' && str[1] == '>'))
		return (2);
	if (str[0] == '<' || str[0] == '|' || str[0] == '>')
		return (1);
	return (0);
}

int	get_word_len(char *str)
{
	int		i;
	t_state	state;

	i = 0;
	state = DEFAULT;
	while (str[i])
	{
		set_state(str[i], &state);
		if (state == DEFAULT && (str[i] == ' ' || is_metachar(str[i])))
			break ;
		i++;
	}
	return (i);
}

void	set_state(char c, t_state *state)
{
	if (c == '\'' && *state == DEFAULT)
		*state = IN_SINGLE_QUOTE;
	else if (c == '"' && *state == DEFAULT)
		*state = IN_DOUBLE_QUOTE;
	else if ((c == '\'' && *state == IN_SINGLE_QUOTE) || (c == '"'
			&& *state == IN_DOUBLE_QUOTE))
		*state = DEFAULT;
}
