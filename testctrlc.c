/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   testctrlc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttiprez <ttiprez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/02 15:53:02 by afournie          #+#    #+#             */
/*   Updated: 2026/02/07 17:19:25 by ttiprez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <readline/history.h>
#include <readline/readline.h>
#include <signal.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int	ft_strcmp(const char *s1, const char *s2)
{
	size_t	i;

	i = -1;
	while (s1[++i] && s2[i])
		if (s1[i] != s2[i])
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

char	*ft_strdup(const char *src)
{
	size_t	i;
	size_t	len;
	char	*dup_str;

	len = 0;
	while (src[len])
		len++;
	dup_str = malloc(len + 1);
	if (!dup_str)
		return (NULL);
	dup_str[len] = '\0';
	i = -1;
	while (src[++i])
		dup_str[i] = src[i];
	return (dup_str);
}

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
	char	*last_rl;
	char	*rl;

	while (1)
	{
		rl = readline("Prompt > ");
		if (!rl)
			exit(0);
		if (last_rl)
			if (ft_strcmp(rl, "") && ft_strcmp(rl, last_rl))
				add_history(rl);
		last_rl = ft_strdup(rl);
		exec_cmd(rl);
	}
}

int	main(void)
{
	init_signal();
	prompt();
	return (EXIT_SUCCESS);
}
