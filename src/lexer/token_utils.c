/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttiprez <ttiprez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/23 11:29:34 by ttiprez           #+#    #+#             */
/*   Updated: 2026/03/23 11:50:32 by ttiprez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*ft_token_new(char *content, t_token_type type)
{
	t_token	*token;

	token = malloc(sizeof(t_token));
	token->content = content;
	token->type = type;
	token->next = NULL;
	token->prev = NULL;
}

t_token	*ft_token_get_last(t_token **lst)
{
	t_token	*current;

	current = *lst;
	while (current->next)
		current = current->next;
	return (current);
}

void	ft_token_add_back(t_token **lst, t_token *new)
{
	t_token	*last;

	last = ft_token_get_last(lst);
	last->next = new;
	new->prev = last;
}

void	ft_token_clear(t_token	**lst)
{
	t_token	*current;
	t_token	*next;

	current = *lst;
	next = current->next;
	while (current)
	{
		free(current->content);
		free(current);
		current = next;
		next = current->next;
	}
}

t_token_type	get_operator_type(char *str)
{
	if (str[0] == '<' && str[1] == '<')
		return (HEREDOC);
	else if (str[0] == '>' && str[1] == '>')
		return (APPEND);
	else if (str[0] == '|')
		return (PIPE);
	else if (str[0] == '>')
		return (OUTPUT);
	else if (str[0] == '<')
		return (INPUT);
	else
		return (WORD);
}
