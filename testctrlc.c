/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   testctrlc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afournie <afournie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/02 15:53:02 by afournie          #+#    #+#             */
/*   Updated: 2026/02/02 16:55:29 by afournie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <readline/history.h>
#include <readline/readline.h>
#include <signal.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

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
void exec_pwd()
{

}
void	exec_cmd(char *rl)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (rl[i])
	{
		if (i == 0 && rl[i] == 'p')
			j++;
		if (i == 1 && rl[i] == 'w')
			j++;
		if (i == 2 && rl[i] == 'd')
			j++;
		i++;
	}
	if (j == 3)
		printf("pwd:%s\n", getcwd(NULL, 0));
}

void	prompt(void)
{
	char	*rl;

	while (1)
	{
		rl = readline("Prompt > ");
		if (!rl)
			exit(0);
		add_history(rl);
		exec_cmd(rl);
	}
}

int	main(void)
{
	init_signal();
	prompt();
	return (EXIT_SUCCESS);
}
