/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afournie <afournie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/06 15:29:44 by ttiprez           #+#    #+#             */
/*   Updated: 2026/03/06 17:23:23 by afournie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	expand(char **tokens)
{
	int		i;
	t_state	state;

	state = DEFAULT;
	while (*tokens)
	{
		i = -1;
		while (*tokens[i])
		{
			if (*tokens[i] == '\'' && state == DEFAULT)
				state = IN_SINGLE_QUOTE;
			else if (*tokens[i] == '"' && state == DEFAULT)
				state = IN_DOUBLE_QUOTE;
			else if ((*tokens[i] == '\'' && state == IN_SINGLE_QUOTE)
				|| (*tokens[i] == '"' && state == IN_DOUBLE_QUOTE))
				state = DEFAULT;
			if (*tokens[i] == '$')
				return ;
		}
		tokens++;
	}
}
