/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttiprez <ttiprez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/09 11:58:18 by ttiprez           #+#    #+#             */
/*   Updated: 2026/04/10 15:56:13 by ttiprez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	exec_cmd(t_cmd *cmd)
{
	if (!cmd->cmd_with_path)
	{
		cmd_not_found(cmd->args[0]);
		exit((free_env(cmd->envp), ft_free(), EXIT_FAILURE));
	}
	execve(cmd->cmd_with_path, cmd->args, cmd->envp);
	perror(cmd->args[0]);
	exit((free_env(cmd->envp), ft_free(), EXIT_FAILURE));
}

static void	handle_redirection(int *input_fd, int *output_fd, t_cmd *current)
{
	int	redir_in;
	int	redir_out;

	redir_in = open_input_file(current);
	if (redir_in != STDIN_FILENO)
		*input_fd = redir_in;
	redir_out = open_output_file(current);
	if (redir_out != STDOUT_FILENO)
		*output_fd = redir_out;
}

static int	child_action(t_cmd *cmd, int from, int to)
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
		return ((perror("fork\n"), -1));
	if (child == 0)
	{
		if (dup2(from, STDIN_FILENO) == -1)
			exit((free_env(cmd->envp), ft_free(), EXIT_FAILURE));
		if (dup2(to, STDOUT_FILENO) == -1)
			exit((free_env(cmd->envp), ft_free(), EXIT_FAILURE));
		close_all_fd();
		exec_cmd(cmd);
	}
	return (0);
}

int	pipex(t_cmd **lst_cmd)
{
	t_cmd	*current;
	int		pipe_fd[2];
	int		input_fd;
	int		output_fd;
	int		last_pid;

	free((current = *lst_cmd, input_fd = STDIN_FILENO, last_pid = 0, NULL));
	while (current)
	{
		output_fd = STDOUT_FILENO;
		if (current->next)
			free((pipe(pipe_fd), output_fd = pipe_fd[1], NULL));
		handle_redirection(&input_fd, &output_fd, current);
		if (current->args)
		{
			last_pid = child_action(current, input_fd, output_fd);
			if (last_pid < 0)
				return (-1);
		}
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
