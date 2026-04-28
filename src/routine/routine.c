/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttiprez <ttiprez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/09 14:10:33 by afournie          #+#    #+#             */
/*   Updated: 2026/04/28 15:42:49 by ttiprez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	handle_rl(char **rl, t_mini *mini)
{
	if (!(*rl)[0])
		return (free(*rl), false);
	add_history(*rl);
	if (!have_valid_quotes(*rl))
		return (printf("error: unclosed quote\n"), free(*rl), false);
	expand(rl, mini);
	return (true);
}

static t_cmd	*lexer_parser(char *rl, t_env **env)
{
	t_token	*lst_token;
	t_cmd	*lst_cmd;

	lst_token = lexer(rl);
	if (!lst_token)
		return (NULL);
	lst_cmd = parser(&lst_token, env);
	if (!lst_cmd)
	{
		ft_free();
		return (NULL);
	}
	return (lst_cmd);
}

void	shell_prompt(t_mini *mini)
{
	char	*rl;

	while (1)
	{
		free((init_signal(), g_sig = 0, rl = readline("Minishell$ "), NULL));
		if (g_sig == SIGINT)
		{
			free((free(rl), mini->last_exit = EXIT_SIGNAL_BASE + SIGINT, NULL));
			continue;
		}
		if (!rl)
			exit((ft_free(), cleaning(&mini->env), printf("exit\n"),
					mini->last_exit));
		if (!handle_rl(&rl, mini))
			continue ;
		mini->cmds = lexer_parser(rl, &mini->env);
		if (!mini->cmds)
			continue ;
		if (!preprocess_heredocs(&mini->cmds, mini))
			continue ;
		ignore_signals_parent();
		mini->last_exit = pipex(mini);
		free((delete_heredocs_files(&mini->cmds), ft_free(), NULL));
	}
	cleaning(&mini->env);
}
