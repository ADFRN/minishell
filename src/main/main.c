/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afournie <afournie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/12 13:48:40 by ttiprez           #+#    #+#             */
/*   Updated: 2026/04/08 12:12:56 by afournie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	exec_cmd(t_cmd *cmd, char **envp)
{
	if (!get_cmd_with_path(cmd->args[0], get_path(envp)))
	{
		cmd_not_found(cmd->args[0]);
		exit((ft_free(), close_all_fd(), EXIT_FAILURE));
	}
	execve(get_cmd_with_path(cmd->args[0], get_path(envp)), cmd->args, envp);
	perror(cmd->args[0]);
}

static int	child_action(t_cmd *cmd, int from, char **envp)
{
	pid_t	child;

	if (from < 0)
		return (0);
	child = fork();
	if (child == -1)
		exit((printf("fail\n"), EXIT_FAILURE)); // fail
	if (child == 0)
	{
		if (dup2(from, STDIN_FILENO) == -1)
			return (1);
		close(from);
		close_all_fd();
		exec_cmd(cmd, envp);
	}
	return (0);
}

static int	pipex(t_cmd **lst_cmd, char **envp)
{
	t_cmd	*current;
	int		input_fd;
	int		last_pid;

	current = *lst_cmd;
	last_pid = 0;
	while (current)
	{
		if (current->redir_in)
		{
			input_fd = open(current->redir_in, O_RDONLY);
			// GERER LE FAIL
		}
		if (current->args[0])
		{
			last_pid = child_action(current, input_fd, envp);
		}
		current = current->next;
	}
	return (wait_for_children(last_pid));
}

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
		printf("rl : %s \n", rl);
		if (!rl)
		{
			printf("exit\n");
			break ;
		}
		if (rl[0] == '\0')
		{
			free(rl);
			continue ;
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
		printf("\nrl expand : %s\n\n", rl);
		lst_token = tokenizer(rl);
		if (!lst_token)
			continue ;
		// AFFICHAGE
		lst_cmd = parser(&lst_token);
		pipex(&lst_cmd, envcpy);
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
