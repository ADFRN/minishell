/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttiprez <ttiprez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/27 10:28:25 by ttiprez           #+#    #+#             */
/*   Updated: 2026/04/27 11:42:19 by ttiprez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	t_redirection	*redir_lst;
	t_redirection	*redir;

	curr = *start;
	redir_lst = NULL;
	while (curr && curr->type != PIPE)
	{
		if (curr->type == INPUT || curr->type == HEREDOC
			|| curr->type == OUTPUT || curr->type == APPEND)
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

static t_token	*go_to_next_cmd(t_token **start)
{
	t_token	*current;

	current = *start;
	while (current && current->type != PIPE)
		current = current->next;
	if (!current)
		return (NULL);
	return (current->next);
}

t_cmd	*parser(t_token **token_lst, t_env **env)
{
	t_token	*c_token;
	t_cmd	*c_cmd;
	t_cmd	*lst_cmd;

	if (!check_syntax(*token_lst, env))
		return (ft_token_clear(token_lst), NULL);
	lst_cmd = ft_cmd_new();
	free((c_cmd = lst_cmd, c_token = *token_lst, NULL));
	while (c_token)
	{
		c_cmd->args = get_cmd_args(&c_token);
		c_cmd->cmd_with_path = NULL;
		if (c_cmd->args && c_cmd->args[0])
		{
			c_cmd->cmd_with_path = get_cmd_with_path(c_cmd->args[0],
					ft_env_get_val(*env, "PATH"));
		}
		c_cmd->redir = get_cmd_redir(&c_token);
		c_token = go_to_next_cmd(&c_token);
		if (c_token)
			free((c_cmd->next = ft_cmd_new(), c_cmd = c_cmd->next, NULL));
	}
	return (lst_cmd);
}
