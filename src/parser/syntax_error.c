/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttiprez <ttiprez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/09 14:14:20 by ttiprez           #+#    #+#             */
/*   Updated: 2026/04/09 14:17:35 by ttiprez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	report_syntax_error(char *token_content)
{
	if (token_content)
		printf("minishell: syntax error near unexpected token `%s'\n",
			token_content);
	else
		printf("minishell: syntax error near unexpected token `newline'\n");
	return (false);
}

static bool	is_redir(int type)
{
	return (type == INPUT || type == OUTPUT || type == HEREDOC
		|| type == APPEND);
}

bool	check_syntax(t_token *token_lst)
{
	t_token	*current;

	current = token_lst;
	while (current)
	{
		if (current->type == PIPE)
		{
			if (!current->prev || !current->next || current->next->type == PIPE)
				return (report_syntax_error("|"));
		}
		else if (is_redir(current->type))
		{
			if (!current->next)
				return (report_syntax_error(NULL));
			if (current->next->type != WORD)
				return (report_syntax_error(current->next->content));
		}
		current = current->next;
	}
	return (true);
}