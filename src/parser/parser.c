/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttiprez <ttiprez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/27 10:28:25 by ttiprez           #+#    #+#             */
/*   Updated: 2026/04/15 16:35:59 by ttiprez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//static void	fill_redir_in(t_token **lst_token, t_cmd **cmd)
//{
//	t_redirection	*new;

//	new = ft_redir_new(ft_strdup((*lst_token)->next->content),
//			(*lst_token)->type == HEREDOC);
//	ft_redir_add_back(&(*cmd)->redir_in, new);
//}

//static void	fill_redir_out(t_token **lst_token, t_cmd **cmd)
//{
//	t_redirection	*new;

//	new = ft_redir_new(ft_strdup((*lst_token)->next->content),
//			(*lst_token)->type == APPEND);
//	ft_redir_add_back(&(*cmd)->redir_out, new);
//}

//static void	fill_cmd(t_token **lst_token, t_cmd **cmd)
//{
//	if ((*lst_token)->type == WORD)
//	{
//		(*cmd)->args = ft_token_to_args(lst_token);
//		(*cmd)->cmd_with_path = get_cmd_with_path((*cmd)->args[0],
//				get_path((*cmd)->envp));
//		return ;
//	}
//	if ((*lst_token)->type == INPUT || (*lst_token)->type == HEREDOC)
//		fill_redir_in(lst_token, cmd);
//	else if ((*lst_token)->type == OUTPUT || (*lst_token)->type == APPEND)
//		fill_redir_out(lst_token, cmd);
//	(*lst_token) = (*lst_token)->next->next;
//}

//t_cmd	*parser(t_token **token_lst, char **env)
//{
//	t_token	*current_token;
//	t_cmd	*current_cmd;
//	t_cmd	*lst_cmd;

//	if (!check_syntax(*token_lst, env))
//		return (ft_token_clear(token_lst), NULL); // TODO: Fake le here_doc
//	lst_cmd = ft_cmd_new();
//	current_cmd = lst_cmd;
//	current_token = *token_lst;
//	while (current_token)
//	{
//		current_cmd->envp = env;
//		if (current_token->type == PIPE)
//		{
//			current_cmd->next = ft_cmd_new();
//			current_cmd = current_cmd->next;
//			current_token = current_token->next;
//		}
//		else
//			fill_cmd(&current_token, &current_cmd);
//	}
//	return (ft_token_clear(token_lst), lst_cmd);
//}

static t_redir_type	get_redir_type(t_token_type token_type)
{
	if (token_type == INPUT)
		return (REDIR_IN);
	if (token_type == HEREDOC)
		return (REDIR_HEREDOC);
	if (token_type == OUTPUT)
		return (REDIR_OUT);
	if (token_type == APPEND)
		return (REDIR_APPEND);
	return (-1);
}

static t_redirection	*get_cmd_redir(t_token **start)
{
	t_token			*curr;
	int				redir_len;
	t_redirection	*redir_lst;
	t_redirection	*redir;

	curr = *start;
	redir_len = 0;
	redir_lst = NULL;
	while (curr && curr->type != PIPE)
	{
		if (curr->type == INPUT || curr->type == HEREDOC || \
			curr->type == OUTPUT || curr->type == APPEND)
		{
			redir = ft_redir_new();
			redir->filename = curr->next->content;
			redir->redir_type = get_redir_type(curr->type);
			ft_redir_add_back(&redir_lst, redir);
		}
		curr = curr->next;
	}
	return (redir_lst);
}

static	t_token	*go_to_next_cmd(t_token	**start)
{
	t_token	*current;

	current = *start;
	while (current->next && current->type != PIPE)
		current = current->next;
	return (current->next);
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
		printf("current_token = %s\n", current_token->content);
		current_cmd->envp = env;
		current_cmd->args = get_cmd_args(&current_token);
		current_cmd->cmd_with_path = \
			get_cmd_with_path(current_cmd->args[0], get_path(env));
		current_cmd->redir = get_cmd_redir(&current_token);
		current_cmd = current_cmd->next;
		current_cmd = ft_cmd_new();
		current_token = go_to_next_cmd(&current_token);
	}
	return (lst_cmd);
}
