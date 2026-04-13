/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afournie <afournie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/12 13:48:40 by ttiprez           #+#    #+#             */
/*   Updated: 2026/04/10 14:49:57 by afournie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int ac, char **av, char **envp)
{
	t_cmd	*lst_cmd;

	(void)ac;
	(void)av;
	init_signal();
	lst_cmd->envp = env_cpy(envp);
	shell_prompt(lst_cmd);
	free_env(lst_cmd->envp);
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
