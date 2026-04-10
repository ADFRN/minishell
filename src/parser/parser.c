/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttiprez <ttiprez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/27 10:28:25 by ttiprez           #+#    #+#             */
/*   Updated: 2026/04/10 15:09:06 by ttiprez          ###   ########.fr       */
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
	t_redirection	*new;
	
	new = ft_redir_new(ft_strdup((*lst_token)->next->content), \
		(*lst_token)->type == HEREDOC);
	ft_redir_add_back(&(*cmd)->redir_in, new);
}

static void	fill_redir_out(t_token **lst_token, t_cmd **cmd)
{
	t_redirection	*new;
	
	new = ft_redir_new(ft_strdup((*lst_token)->next->content), \
		(*lst_token)->type == APPEND);
	ft_redir_add_back(&(*cmd)->redir_out, new);
}

static void	fill_cmd(t_token **lst_token, t_cmd **cmd)
{
	if ((*lst_token)->type == WORD)
	{
		(*cmd)->args = ft_token_to_args(lst_token);
		(*cmd)->cmd_with_path = get_cmd_with_path((*cmd)->args[0], \
			get_path((*cmd)->envp));
		return ;
	}
	if ((*lst_token)->type == INPUT || (*lst_token)->type == HEREDOC)
		fill_redir_in(lst_token, cmd);
	else if ((*lst_token)->type == OUTPUT || (*lst_token)->type == APPEND)
		fill_redir_out(lst_token, cmd);
	(*lst_token) = (*lst_token)->next->next;
}

t_cmd	*parser(t_token **token_lst, char **env)
{
	t_token	*current_token;
	t_cmd	*current_cmd;
	t_cmd	*lst_cmd;

	if (!check_syntax(*token_lst, env))
		return (ft_token_clear(token_lst), NULL);
	lst_cmd = ft_cmd_new();
	current_cmd = lst_cmd;
	current_token = *token_lst;
	while (current_token)
	{
		current_cmd->envp = env;
		if (current_token->type == PIPE)
		{
			current_cmd->next = ft_cmd_new();
			current_cmd = current_cmd->next;
			current_token = current_token->next;
		}
		else
			fill_cmd(&current_token, &current_cmd);
	}
	return (ft_token_clear(token_lst), lst_cmd);
}
