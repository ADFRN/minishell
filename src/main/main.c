/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttiprez <ttiprez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/12 13:48:40 by ttiprez           #+#    #+#             */
/*   Updated: 2026/04/03 18:58:03 by ttiprez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	shell_prompt(char **envcpy)
{
	char	*rl;
	t_token	*lst_token;
	t_cmd	*lst_cmd;

	lst_token = NULL;
	// MINISHELL
	while (1)
	{
		// READLINE
		rl = readline("Minishell-1.0$ ");
		if (!rl)
			break;
		if (rl[0] == '\0')
		{
			free(rl);
			continue;
		}
		add_history(rl);

		// VERIFICATION READLINE
		if (!have_valid_quotes(rl))
		{
			printf("error: unclosed quote\n");
			free(rl);
			continue ;
		}

		// LEXER
		expand(&rl, envcpy);
		printf("\nrl : %s\n\n", rl);
		lst_token = tokenizer(rl);
		if (!lst_token)
			continue;

		// AFFICHAGE
		lst_cmd = parser(&lst_token);
		ft_token_clear(&lst_token);
		ft_print_lst_cmd(&lst_cmd);

		// FREE
		ft_free();
	}
	// LAST FREE
	ft_free();
}

int	main(int ac, char **av, char **envp)
{
	char	**envcpy;

	(void)ac;
	(void)av;
	init_signal();
	envcpy = env_cpy(envp);
	shell_prompt(envcpy);
	free_env(envcpy);
	return (EXIT_SUCCESS);
}
