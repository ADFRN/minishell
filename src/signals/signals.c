/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afournie <afournie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/02 15:53:02 by afournie          #+#    #+#             */
/*   Updated: 2026/04/07 12:17:33 by afournie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ctrlc_handler(int sig, siginfo_t *info, void *context)
{
	(void)info;
	(void)context;
	if (sig == SIGINT)
	{
		write(1, "\n", 1);
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
}

void	init_signal(void)
{
	struct sigaction	sa;
	struct sigaction	sa_ignore;

	ft_memset(&sa, 0, sizeof(sa));
	sa.sa_sigaction = &ctrlc_handler;
	sa.sa_flags = SA_SIGINFO;
	sigemptyset(&sa.sa_mask);
	sigaction(SIGINT, &sa, NULL);
	ft_memset(&sa_ignore, 0, sizeof(sa_ignore));
	sa_ignore.sa_handler = SIG_IGN;
	sigemptyset(&sa_ignore.sa_mask);
	sigaction(SIGQUIT, &sa_ignore, NULL);
}

// After the fork (if (pid == 0) before execve)

void	reset_signals_child(void)
{
	struct sigaction	sa;

	ft_memset(&sa, 0, sizeof(sa));
	sa.sa_handler = SIG_DFL;
	sigemptyset(&sa.sa_mask);
	sigaction(SIGINT, &sa, NULL);
	sigaction(SIGQUIT, &sa, NULL);
}

// int status;
// waitpid(pid, &status, 0);

// if (WIFSIGNALED(status) && WTERMSIG(status) == SIGQUIT)
//     write(2, "Quit (core dumped)\n", 19); // comme bash
