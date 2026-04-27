/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttiprez <ttiprez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/09 14:10:33 by afournie          #+#    #+#             */
/*   Updated: 2026/04/27 11:51:50 by ttiprez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	handle_rl(char **rl, t_env *env)
{
	if (!(*rl)[0])
		return (free(*rl), false);
	add_history(*rl);
	if (!have_valid_quotes(*rl))
		return (printf("error: unclosed quote\n"), free(*rl), false);
	expand(rl, env);
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
		init_signal();
		rl = readline("Minishell-1.0$ ");
		if (!rl)
			exit((cleaning(&mini->env), printf("exit\n"), 0));
		if (!handle_rl(&rl, mini->env))
			continue ;
		mini->cmds = lexer_parser(rl, &mini->env);
		if (!mini->cmds)
			continue ;
		if (!preprocess_heredocs(&mini->cmds))
			continue ;
		ignore_signals_parent();
		pipex(mini);
		delete_heredocs_files(&mini->cmds);
		ft_free();
	}
	cleaning(&mini->env);
}
