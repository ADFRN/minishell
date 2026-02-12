/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttiprez <ttiprez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/12 13:48:40 by ttiprez           #+#    #+#             */
/*   Updated: 2026/02/12 14:43:58 by ttiprez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>

static void	shell_prompt(void)
{
	char	*last_rl;
	char	*rl;

	while (1)
	{
		rl = readline("[usernaame]@[hostname]:[current_directory]$ ");
		if (!rl)
			exit(0);
		if (last_rl)
			if (ft_strcmp(rl, "") && ft_strcmp(rl, last_rl))
				add_history(rl);
		last_rl = ft_strdup(rl);
		exec_cmd(rl);
		printf("%s\n", rl);
	}
}

int	main(void)
{
	init_signal();
	shell_prompt();
	return (EXIT_SUCCESS);
}
