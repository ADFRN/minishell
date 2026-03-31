/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afournie <afournie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/27 10:28:25 by ttiprez           #+#    #+#             */
/*   Updated: 2026/03/31 13:52:33 by afournie         ###   ########.fr       */
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

static bool	check_syntax(t_token *token_lst)
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

static void	fill_cmd(t_token **lst_token, t_cmd **cmd)
{
	if ((*lst_token)->type == WORD)
	{
		(*cmd)->args = ft_token_to_args(lst_token);
		return ;
	}
	if ((*lst_token)->type == INPUT)
		(*cmd)->redir_in = ft_strdup((*lst_token)->next->content);
	else if ((*lst_token)->type == OUTPUT)
		(*cmd)->redir_out = ft_strdup((*lst_token)->next->content);
	else if ((*lst_token)->type == HEREDOC)
	{
		(*cmd)->redir_in = ft_strdup((*lst_token)->next->content);
		(*cmd)->heredoc = true;
	}
	else if ((*lst_token)->type == APPEND)
	{
		(*cmd)->redir_out = ft_strdup((*lst_token)->next->content);
		(*cmd)->append = true;
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
