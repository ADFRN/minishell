/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttiprez <ttiprez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/12 13:48:40 by ttiprez           #+#    #+#             */
/*   Updated: 2026/04/13 15:05:28 by ttiprez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void shell_prompt(char **envcpy)
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
		{
			printf("exit\n");
			break;
		}
		if (rl[0] == '\0')
		{
			free(rl);
			continue;
		}
		add_history(rl);
		// VERIFICATION READLINE
		if (!have_valid_quotes(rl))
		{
			free((free(rl), printf("error: unclosed quote\n"), NULL));
			continue;
		}
		// LEXER
		expand(&rl, envcpy);
		lst_token = lexer(rl);
		if (!lst_token)
			continue;
		// AFFICHAGE
		lst_cmd = parser(&lst_token, envcpy);
		pipex(&lst_cmd);
		// FREE
		ft_free();
		close_all_fd();
	}
	// LAST FREE
	close_all_fd();
	ft_free();
}

int main(int ac, char **av, char **envp)
{
	char **envcpy;

	(void)ac;
	(void)av;
	init_signal();
	envcpy = env_cpy(envp);
	shell_prompt(envcpy);
	free_env(envcpy);
	return (EXIT_SUCCESS);
}

// int	main(int ac, char **av, char **envp)
//{
//	t_lstcmd	*lstcmd;
//	int			fd_in;
//	int			fd_out;
//	int			exit_status;

//	fd_out = open_output_file(av[ac - 1], is_heredoc(av));
//	fd_in = open_input_file(av[1], av);
//	if (fd_in == -2)
//		return (cleanup(NULL, fd_in, fd_out), EXIT_FAILURE);
//	lstcmd = init_lstcmd(is_heredoc(av), ac, av, envp);
//	if (!lstcmd)
//		return (cleanup(NULL, fd_in, fd_out), EXIT_FAILURE);
//	exit_status = execute_pipeline(lstcmd, fd_in, fd_out);
//	return (cleanup(lstcmd, fd_in, fd_out), exit_status);
//}
