/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttiprez <ttiprez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/09 14:10:33 by afournie          #+#    #+#             */
/*   Updated: 2026/04/21 16:21:02 by ttiprez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	handle_rl(char **rl, char **envcpy)
{
	if (!(*rl)[0])
		return (free(*rl), false);
	add_history(*rl);
	if (!have_valid_quotes(*rl))
		return (printf("error: unclosed quote\n"), free(*rl), false);
	expand(rl, envcpy);
	return (true);
}

t_cmd	*lexer_parser(char *rl, char **env)
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

void	shell_prompt(char **envcpy)
{
	char	*rl;
	t_cmd	*lst_cmd;

	while (1)
	{
		init_signal();
		rl = readline("Minishell-1.0$ ");
		if (!rl)
		{
			exit((printf("exit\n"), 0));
			break ;
		}
		if (!handle_rl(&rl, envcpy))
			continue ;
		lst_cmd = lexer_parser(rl, envcpy);
		if (!lst_cmd)
			continue ;
		if (!preprocess_heredocs(&lst_cmd))
			continue ;
		ignore_signals_parent();
		pipex(&lst_cmd);
		delete_heredocs_files(&lst_cmd);
		ft_free();
	}
	cleaning(envcpy);
}
