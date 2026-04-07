/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttiprez <ttiprez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/12 13:48:40 by ttiprez           #+#    #+#             */
/*   Updated: 2026/04/07 15:54:27 by ttiprez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	check_fd_access(t_cmd *current)
{
	if (current->redir_in && !current->heredoc)
	{
		if (access(current->redir_in, F_OK) == -1)
			perror(current->redir_in);
		else if (access(current->redir_in, R_OK) == -1)
			perror(current->redir_in);
	}
	if (current->redir_out)
	{
		if (access(current->redir_out, F_OK) == 0
			&& access(current->redir_out, W_OK) == -1)
			perror(current->redir_out);
	}
}

static int	ft_execve(t_cmd *cmd, char **envcpy)
{
	if (!get_cmd_with_path(cmd->args[0], get_path(envcpy)))
	{
		cmd_not_found(cmd->args[0]);
		return (CMD_NOT_FOUND);
	}
	execve(get_cmd_with_path(cmd->args[0], get_path(envcpy)), cmd->args, envcpy);
	perror(cmd->args[0]);
	return (CMD_EXEC_ERROR);
}

static int	child_action(t_cmd *cmd, char **envcpy, int from, int to)
{
	pid_t	child;

	if (from < 0)
	{
		if (to >= 0)
			close(to);
		return (0);
	}
	child = fork();
	if (child == -1)
		exit((perror("fork()"), close_all_fd(), ft_free(), 1));
	if (child == 0)
	{
		if (dup2(from, STDIN_FILENO) == -1)
			exit((ft_free(), EXIT_FAILURE));
		if (dup2(to, STDOUT_FILENO) == -1)
			exit((ft_free(), EXIT_FAILURE));
		close(to);
		close(from);
		close_all_fd();
		ft_execve(cmd, envcpy);
	}
	return (close(from), close(to), child);
}

static int execute_command(t_cmd *cmd, char **envcpy, int *fd_in, int *fd_out)
{
	int	pipe_fd[2];
	int	last_pid;

	last_pid = 0;
	if (cmd->next)
	{
		if (pipe(pipe_fd) == -1)
			return (perror("pipe"), -1);
		*fd_out = pipe_fd[1];
	}
	last_pid = child_action(cmd, envcpy, *fd_in, *fd_out);
	if (cmd->next)
		*fd_in = pipe_fd[0];
	return (last_pid);
}

static int	execute_pipeline(t_cmd	**lst_cmd, char **envcpy)
{
	t_cmd	*current;
	int		last_pid;
	int		fd_in;
	int		fd_out;

	current = *lst_cmd;
	while (current)
	{
		check_fd_access(current);
		if (current->redir_in)
		{
			fd_in = open_input_file(current);
			dup2(fd_in, STDIN_FILENO);
		}
		if (current->redir_out)
		{
			fd_out = open_output_file(current);
			dup2(fd_out, STDOUT_FILENO);
		}
		last_pid = execute_command(current, envcpy, &fd_in, &fd_out);
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
		execute_pipeline(&lst_cmd, envcpy);
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

//int	main(int ac, char **av, char **envp)
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
