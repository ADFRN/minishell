/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttiprez <ttiprez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/12 13:48:40 by ttiprez           #+#    #+#             */
/*   Updated: 2026/03/24 12:51:44 by ttiprez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	shell_prompt(int ac, char **av, char **envcpy)
{
	char	*rl;
	t_token	*lst_token;

	lst_token = NULL;
	while (1)
	{
		rl = readline("[username]@[hostname]:[current_directory]$ ");
		if (!rl)
			exit(0);
		add_history(rl);
		printf("%s\n", rl);
		suitebordel(ac, av, envcpy);
		//expand(lst_token, envcpy);
		if (!have_valid_quotes(rl))
		{
			printf("error: unclosed quote\n");	
			return ;
		}
		lst_token = tokenizer(rl);
		if (!lst_token)
			exit(EXIT_FAILURE);
		print_tokens(&lst_token);
	}
}

int	main(int ac, char **av, char **envp)
{
	char	**envcpy;

	init_signal();
	envcpy = env_cpy(envp);
	shell_prompt(ac, av, envcpy);
	return (EXIT_SUCCESS);
}
