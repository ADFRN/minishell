/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afournie <afournie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/09 11:58:18 by ttiprez           #+#    #+#             */
/*   Updated: 2026/04/09 12:27:00 by afournie         ###   ########.fr       */
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

int pipex(t_cmd **lst_cmd, char **envp)
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
