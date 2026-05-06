/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_manager.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afournie <afournie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/16 11:53:02 by ttiprez           #+#    #+#             */
/*   Updated: 2026/05/04 17:16:24 by afournie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	preoretesrww(t_cmd *curr_cmd, t_redirection *curr_redir)
{
	while (curr_cmd)
	{
		curr_redir = curr_cmd->redir;
		while (curr_redir)
		{
			if (curr_redir->redir_type == REDIR_HEREDOC)
			{
				curr_redir->filename = run_heredoc(curr_redir);
				if (!curr_redir->filename || g_sig == SIGINT)
					break ;
			}
			curr_redir = curr_redir->next;
		}
		if (g_sig == SIGINT)
			break ;
		curr_cmd = curr_cmd->next;
	}
}

bool	preprocess_heredocs(t_cmd **lst_cmd, t_mini *mini)
{
	t_cmd			*curr_cmd;
	t_redirection	*curr_redir;
	int				saved_stdin;

	saved_stdin = dup(STDIN_FILENO);
	curr_cmd = *lst_cmd;
	curr_redir = NULL;
	signal(SIGINT, ctrlc_heredoc_handler);
	preoretesrww(curr_cmd, curr_redir);
	dup2(saved_stdin, 0);
	close(saved_stdin);
	init_signal();
	if (g_sig == SIGINT)
		return (mini->last_exit = EXIT_SIGNAL_BASE + g_sig, g_sig = 0, false);
	return (mini->last_exit = EXIT_SUCCESS, true);
}

void	delete_heredocs_files(t_cmd **lst_cmd)
{
	t_cmd			*curr_cmd;
	t_redirection	*curr_redir;

	curr_cmd = *lst_cmd;
	while (curr_cmd)
	{
		curr_redir = curr_cmd->redir;
		while (curr_redir)
		{
			if (curr_redir->redir_type == REDIR_HEREDOC)
				unlink(curr_redir->filename);
			curr_redir = curr_redir->next;
		}
		curr_cmd = curr_cmd->next;
	}
}
