/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttiprez <ttiprez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/27 10:28:25 by ttiprez           #+#    #+#             */
/*   Updated: 2026/04/09 15:27:18 by ttiprez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// TO-DO :
//	Verifier si la grammaire est respecte :
//		... PIPE PIPE ... 	-> ERREUR	bash: syntax error near unexpected token `|'
//		PIPE ...			-> ERREUR	bash: syntax error near unexpected token `|'
//		... PIPE			-> OK		Affiche > et attend la fin (A gerer comme une erreur)
//		... REDIR_INT		-> ERREUR	bash: syntax error near unexpected token `newline'
//		... REDIR_OUT		-> ERREUR	bash: syntax error near unexpected token `newline'
//		WORD PIPE WORD REDIR_OUT FILE REDIR_IN FILE PIPE WORD		-> OK

#include "minishell.h"

static void	fill_redir_in(t_token **lst_token, t_cmd **cmd)
{
	if (!(*cmd)->redir_in)
	{
		
	}
}

static void	fill_cmd(t_token **lst_token, t_cmd **cmd)
{
	if ((*lst_token)->type == WORD)
	{
		(*cmd)->args = ft_token_to_args(lst_token);
		return ;
	}
	if ((*lst_token)->type == INPUT || (*lst_token)->type == HEREDOC)
	{
		fill_redir_in(lst_token, cmd);
		(*cmd)->redir_in = ft_strdup((*lst_token)->next->content);
	}
	else if ((*lst_token)->type == OUTPUT)
		(*cmd)->redir_out = ft_strdup((*lst_token)->next->content);
	else if ((*lst_token)->type == APPEND)
	{
		(*cmd)->redir_out = ft_strdup((*lst_token)->next->content);
	}
	(*lst_token) = (*lst_token)->next->next;
}

t_cmd	*parser(t_token **token_lst)
{
	t_token	*current_token;
	t_cmd	*current_cmd;
	t_cmd	*lst_cmd;

	if (!check_syntax(*token_lst))
		return (NULL);
	lst_cmd = ft_cmd_new();
	current_cmd = lst_cmd;
	current_token = *token_lst;
	while (current_token)
	{
		if (current_token->type == PIPE)
		{
			current_cmd->next = ft_cmd_new();
			current_cmd = current_cmd->next;
			current_token = current_token->next;
		}
		else
			fill_cmd(&current_token, &current_cmd);
	}
	return (lst_cmd);
}
