/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttiprez <ttiprez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/12 13:48:40 by ttiprez           #+#    #+#             */
/*   Updated: 2026/03/05 13:52:47 by ttiprez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>

static void	shell_prompt(void)
{
	char	*rl;

	while (1)
	{
		rl = readline("[username]@[hostname]:[current_directory]$ ");
		if (!rl)
			exit(0);
		add_history(rl);
		exec_cmd(rl);
		printf("%s\n", rl);
		printf("nb_words = %d\n", count_words(rl));
		if (!check_quotes(rl))
			printf("error: unclosed quote\n");
	}
}

int	main(void)
{
	init_signal();
	shell_prompt();
	return (EXIT_SUCCESS);
}
