/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afournie <afournie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/12 13:48:40 by ttiprez           #+#    #+#             */
/*   Updated: 2026/03/06 17:39:35 by afournie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

static void	shell_prompt(void)
{
	char	*rl;
	char	**tokens;

	while (1)
	{
		rl = readline("[username]@[hostname]:[current_directory]$ ");
		if (!rl)
			exit(0);
		add_history(rl);
		printf("%s\n", rl);
		tokens = lexer(rl, 0);
		if (!tokens)
			exit(EXIT_FAILURE);
		expand(tokens);
		if (!have_valid_quotes(rl))
			printf("error: unclosed quote\n");
		print_split(tokens);
		free_split(tokens);
	}
}

int	main(int ac, char **av, char **envp)
{
	init_signal();
	shell_prompt();
	return (EXIT_SUCCESS);
}
