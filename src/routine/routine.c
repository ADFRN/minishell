/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttiprez <ttiprez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/09 14:10:33 by afournie          #+#    #+#             */
/*   Updated: 2026/04/15 16:26:44 by ttiprez          ###   ########.fr       */
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

void	shell_prompt(char **envcpy)
{
	char	*rl;
	t_token	*lst_token;
	t_cmd	*lst_cmd;

	while (1)
	{
		init_signal();
		rl = readline("Minishell-1.0$ ");
		if (!rl)
		{
			printf("exit\n");
			break ;
		}
		if (!handle_rl(&rl, envcpy))
			continue;
		lst_token = lexer(rl);
		if (!lst_token)
			continue ;
		print_tokens(&lst_token);
		lst_cmd = parser(&lst_token, envcpy);
		ft_print_lst_cmd(&lst_cmd);
		ignore_signals_parent();
		//pipex(&lst_cmd);
		ft_free();
		close_all_fd();
	}
	close_all_fd();
	ft_free();
}
