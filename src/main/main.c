/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttiprez <ttiprez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/12 13:48:40 by ttiprez           #+#    #+#             */
/*   Updated: 2026/04/08 15:19:04 by ttiprez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void exec_cmd(t_cmd *cmd, char **envp)
{
	if (!get_cmd_with_path(cmd->args[0], get_path(envp)))
	{
		cmd_not_found(cmd->args[0]);
		exit((ft_free(), close_all_fd(), EXIT_FAILURE));
	}
	execve(get_cmd_with_path(cmd->args[0], get_path(envp)), cmd->args, envp);
	perror(cmd->args[0]);
}

static int child_action(t_cmd *cmd, int from, int to, char **envp)
{
	pid_t child;

	if (from < 0)
	{
		if (to >= 0)
			close(to);
		return (0);
	}
	child = fork();
	if (child == -1)
		exit((printf("fail\n"), EXIT_FAILURE)); // TODO:sortir proprement
	if (child == 0)
	{
		if (dup2(from, STDIN_FILENO) == -1)
			return (1); // TODO : sortir proprement
		if (dup2(to, STDOUT_FILENO) == -1)
			return (1); // TODO : sortir proprement
		close_all_fd();
		exec_cmd(cmd, envp);
	}
	return (0); // TODO: sortir proprement
}

static int pipex(t_cmd **lst_cmd, char **envp)
{
	t_cmd *current;
	int pipe_fd[2];
	int input_fd;
	int output_fd;
	int last_pid;

	current = *lst_cmd;
	input_fd = STDIN_FILENO;
	last_pid = 0;
	while (current)
	{
		output_fd = STDOUT_FILENO;
		if (current->next)
		{
			if (pipe(pipe_fd) == -1)
				return (perror("pipe"), -1); // TODO : Gerer ereur
			output_fd = pipe_fd[1];
		}
		if (current->redir_out)
		{
			if (output_fd != STDOUT_FILENO)
				close(output_fd);
			if (current->append)
				output_fd = open(current->redir_out,
								 O_WRONLY | O_CREAT | O_APPEND, 0644);
			else
				output_fd = open(current->redir_out,
								 O_WRONLY | O_CREAT | O_TRUNC, 0644);
		}
		if (current->redir_in) // TODO : Gerer heredoc
			input_fd = open(current->redir_in, O_RDONLY);
		if (current->args)
			last_pid = child_action(current, input_fd, output_fd, envp);
		if (input_fd != STDIN_FILENO)
			close(input_fd);
		if (output_fd != STDOUT_FILENO)
			close(output_fd);
		if (current->next)
			input_fd = pipe_fd[0];
		else
			input_fd = STDIN_FILENO;
		current = current->next;
	}
	return (wait_for_children(last_pid));
}

static void shell_prompt(char **envcpy)
{
	char *rl;
	t_token *lst_token;
	t_cmd *lst_cmd;

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
			continue;
		}
		// LEXER
		expand(&rl, envcpy);
		lst_token = tokenizer(rl);
		if (!lst_token)
			continue;
		// AFFICHAGE
		lst_cmd = parser(&lst_token);
		ft_print_lst_cmd(&lst_cmd);
		pipex(&lst_cmd, envcpy);
		ft_token_clear(&lst_token);
		// FREE
		ft_free();
	}
	// LAST FREE
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
