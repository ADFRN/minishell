/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   testctrlc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttiprez <ttiprez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/02 15:53:02 by afournie          #+#    #+#             */
/*   Updated: 2026/02/12 14:39:35 by ttiprez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <readline/readline.h>
#include <stdlib.h>
#include <stdio.h>
#include <signal.h>

void	ctrlc_handler(int sig, siginfo_t *info, void *context)
{
	if (sig == SIGINT)
	{
		rl_replace_line("EXIT\n", 0);
		rl_point = rl_end;
		rl_redisplay();
		exit(0);
	}
}

void	init_signal(void)
{
	struct sigaction	sa;

	sa.sa_sigaction = &ctrlc_handler;
	sigemptyset(&sa.sa_mask);
	sigaction(SIGINT, &sa, NULL);
}
