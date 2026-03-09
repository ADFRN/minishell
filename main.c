/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afournie <afournie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/12 13:48:40 by ttiprez           #+#    #+#             */
/*   Updated: 2026/03/09 11:08:03 by afournie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/header.h"
#include "includes/minishell.h"

static void	shell_prompt(int ac, char **av, char **envcpy)
{
	char	*rl;
	//char	**tokens;

	while (1)
	{
		rl = readline("[username]@[hostname]:[current_directory]$ ");
		if (!rl)
			exit(0);
		add_history(rl);
		printf("%s\n", rl);
		suitebordel(ac, av, envcpy);
	// 	tokens = lexer(rl, 0);
	// 	if (!tokens)
	// 		exit(EXIT_FAILURE);
	// 	//expand(tokens);
	// 	if (!have_valid_quotes(rl))
	// 		printf("error: unclosed quote\n");
	// 	print_split(tokens);
	// 	free_split(tokens);
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
