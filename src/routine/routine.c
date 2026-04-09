/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afournie <afournie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/09 14:10:33 by afournie          #+#    #+#             */
/*   Updated: 2026/04/09 14:14:52 by afournie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	handle_rl(char **rl, char **envcpy)
{
	if (!(*rl)[0])
		return (free(*rl), 0);
	if (!have_valid_quotes(*rl))
		return (printf("error: unclosed quote\n"), free(*rl), 0);
	add_history(*rl);
	expand(&rl, envcpy);
	return (1);
}

void	shell_prompt(char **envcpy)
{
	char	*rl;
	t_token	*lst_token;
	t_cmd	*lst_cmd;

	lst_token = NULL;
	while (1)
	{
		rl = readline("Minishell-1.0$ ");
		if (!rl)
		{
			printf("exit\n");
			break ;
		}
		if (!handle_rl(&rl, envcpy))
			continue ;
		lst_token = tokenizer(rl);
		if (!lst_token)
			continue ;
		lst_cmd = parser(&lst_token);
		ft_print_lst_cmd(&lst_cmd);
		pipex(&lst_cmd, envcpy);
		ft_token_clear(&lst_token);
		ft_free();
	}
	ft_free();
}
