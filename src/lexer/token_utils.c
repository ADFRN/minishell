/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttiprez <ttiprez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/23 11:29:34 by ttiprez           #+#    #+#             */
/*   Updated: 2026/03/24 12:53:23 by ttiprez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*ft_token_new(char *content, t_token_type type)
{
	t_token	*token;

	token = malloc(sizeof(t_token));
	if (!token)
		return (NULL);
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
	char	type_str[8] = {0};
	if (type == PIPE)
		ft_strcpy(type_str, "PIPE");
	else if (type == HEREDOC)
		ft_strcpy(type_str, "HEREDOC");
	else if (type == APPEND)
		ft_strcpy(type_str, "APPEND");
	else if (type == OUTPUT)
		ft_strcpy(type_str, "OUTPUT");
	else if (type == INPUT)
		ft_strcpy(type_str, "INPUT");
	else if (type == WORD)
		ft_strcpy(type_str, "WORD");
	return (ft_strdup(type_str));			
}

void	print_tokens(t_token **lst)
{
	t_token	*current;

	current = *lst;
	printf("WORD | TYPE\n");
	while (current)
	{
		printf("%-20s | %s\n", current->content, type_to_str(current->type));
		current = current->next;
	}
}
