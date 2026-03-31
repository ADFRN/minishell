/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afournie <afournie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/12 13:48:40 by ttiprez           #+#    #+#             */
/*   Updated: 2026/03/31 13:34:58 by afournie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	shell_prompt(int ac, char **av, char **envcpy)
{
	char	*rl;
	t_token	*lst_token;

	lst_token = NULL;
	// MINISHELL
	while (1)
	{
		// READLINE
		rl = readline("[username]@[hostname]:[current_directory]$ ");

		if (!rl)
			exit(EXIT_FAILURE);
		add_history(rl);

		printf("%s\n", rl);
		lst_token = lexer(rl, 0);
		if (!lst_token)
			exit(EXIT_FAILURE);
		expand(lst_token, envcpy);
		if (!have_valid_quotes(rl))
			printf("error: unclosed quote\n");
		print_split(lst_token);
		free_split(lst_token);

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
		printf("%s\n", rl);
		print_lst_token(&lst_token);
		printf("Expansion...\n");
		expand(&lst_token, envcpy);
		printf("Expanded !\n");
		print_lst_token(&lst_token);

		// FREE
		ft_token_clear(&lst_token);
		free(rl);
	}
	// FREE
	free(rl);
	ft_token_clear(&lst_token);
}


int	main(int ac, char **av, char **envp)
{
	char	**envcpy;

	init_signal();
	envcpy = env_cpy(envp);
	create_prompt_line();
	shell_prompt(ac, av, envcpy);
	return (EXIT_SUCCESS);
}
