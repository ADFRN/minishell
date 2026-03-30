/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttiprez <ttiprez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/12 13:48:40 by ttiprez           #+#    #+#             */
/*   Updated: 2026/03/30 11:16:46 by ttiprez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	shell_prompt(int ac, char **av, char **envcpy)
{
	char	*rl;
	t_token	*lst_token;
	t_cmd	*lst_cmd;

	lst_token = NULL;
	// MINISHELL
	while (1)
	{
		// READLINE
		rl = readline("[username]@[hostname]:[current_directory]$ ");
		if (!rl)
			exit(EXIT_FAILURE);
		add_history(rl);

		suitebordel(ac, av, envcpy);

		// VERIFICATION READLINE
		if (!have_valid_quotes(rl))
		{
			printf("error: unclosed quote\n");	
			free(rl);
			continue ;
		}

		// LEXER
		lst_token = tokenizer(rl);
		if (!lst_token)
			exit(EXIT_FAILURE);
		
		// AFFICHAGE
		printf("\nINPUT : %s\n\n", rl);
		expand(&lst_token, envcpy);

		lst_cmd = parser(&lst_token);
		ft_token_clear(&lst_token);
		//ft_print_lst_cmd(&lst_cmd);

		// FREE
		free(rl);
	}
	// LAST FREE
	free(rl);
	ft_token_clear(&lst_token);
}

int	main(int ac, char **av, char **envp)
{
	char	**envcpy;

	init_signal();
	envcpy = env_cpy(envp);
	shell_prompt(ac, av, envcpy);
	return (EXIT_SUCCESS);
}
