/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttiprez <ttiprez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/23 11:29:34 by ttiprez           #+#    #+#             */
/*   Updated: 2026/04/21 16:20:28 by ttiprez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*ft_token_new(char *content, t_token_type type)
{
	t_token	*token;

	token = ft_malloc(sizeof(t_token));
	if (!token)
		exit((ft_free(), EXIT_FAILURE));
	token->content = content;
	token->type = type;
	token->next = NULL;
	token->prev = NULL;
	return (token);
}

void	ft_token_add_back(t_token **lst, t_token *new)
{
	t_token	*last;

	if (!*lst)
	{
		*lst = new;
		return ;
	}
	last = *lst;
	while (last->next)
		last = last->next;
	last->next = new;
	new->prev = last;
}

void	ft_token_clear(t_token **lst)
{
	t_token	*next;

	if (!lst || !*lst)
		return ;
	while (*lst)
	{
		next = (*lst)->next;
		*lst = next;
	}
}

t_token_type	get_operator_type(char *str)
{
	if (str[0] == '|')
		return (PIPE);
	if (str[0] == '<' && str[1] == '<')
		return (HEREDOC);
	if (str[0] == '>' && str[1] == '>')
		return (APPEND);
	if (str[0] == '>')
		return (OUTPUT);
	if (str[0] == '<')
		return (INPUT);
	return (WORD);
}

char	*type_to_str(t_token_type type)
{
	if (type == PIPE)
		return ("PIPE");
	else if (type == HEREDOC)
		return ("HEREDOC");
	else if (type == APPEND)
		return ("APPEND");
	else if (type == OUTPUT)
		return ("OUTPUT");
	else if (type == INPUT)
		return ("INPUT");
	return ("WORD");
}
