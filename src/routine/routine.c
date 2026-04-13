/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttiprez <ttiprez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/09 14:10:33 by afournie          #+#    #+#             */
/*   Updated: 2026/04/13 16:03:41 by ttiprez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	handle_rl(char **rl, char **envcpy)
{
	if (!(*rl)[0])
		return (free(*rl), 0);
	add_history(*rl);
	if (!have_valid_quotes(*rl))
		return (printf("error: unclosed quote\n"), free(*rl), 0);
	expand(rl, envcpy);
	return (1);
}
void shell_prompt(char **envcpy)
{
	char	*rl;
	t_token	*lst_token;
	t_cmd	*lst_cmd;

	lst_token = NULL;
	// MINISHELL
	while (1)
	{
		// READLINE
		rl = readline("Minishell-1.0$ ");
		if (!rl)
		{
			printf("exit\n");
			break;
		}
		handle_rl(&rl, envcpy);
		lst_token = lexer(rl);
		if (!lst_token)
			continue;
		// AFFICHAGE
		lst_cmd = parser(&lst_token, envcpy);
		pipex(&lst_cmd);
		// FREE
		ft_free();
		close_all_fd();
	}
	// LAST FREE
	close_all_fd();
	ft_free();
}

