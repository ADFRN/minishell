/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttiprez <ttiprez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/09 11:58:18 by ttiprez           #+#    #+#             */
/*   Updated: 2026/04/15 12:53:46 by ttiprez          ###   ########.fr       */
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

static void	child_process(t_cmd *cmd, int from, int to)
{
	if (dup2(from, STDIN_FILENO) == -1 || dup2(to, STDOUT_FILENO) == -1)
		exit(EXIT_FAILURE);
	if (open_input_file(cmd->redir_in) == -1)
		exit(EXIT_FAILURE);
	if (open_output_file(cmd->redir_out) == -1)
		exit(EXIT_FAILURE);
	close_all_fd();
	if (cmd->args)
		exec_cmd(cmd);
	exit(EXIT_FAILURE);
}

static int	child_action(t_cmd *cmd, int from, int to)
{
	pid_t	pid;

	if (from < 0)
	{
		if (to >= 0)
			close(to);
		return (0);
	}
	pid = fork();
	if (pid == -1)
		return (perror("fork"), -1);
	if (pid == 0)
		child_process(cmd, from, to);
	return (pid);
}

static void	prepare_fds(t_cmd *current, int *output_fd, int pipe_fd[2])
{
	if (current->next)
	{
		if (pipe(pipe_fd) == -1)
			exit(EXIT_FAILURE);
		*output_fd = pipe_fd[1];
	}
	else
		*output_fd = STDOUT_FILENO;
}

int	pipex(t_cmd **lst_cmd)
{
	t_cmd	*current;
	int		pipe_fd[2];
	int		input_fd;
	int		output_fd;
	int		last_pid;

	current = *lst_cmd;
	input_fd = STDIN_FILENO;
	while (current)
	{
		prepare_fds(current, &output_fd, pipe_fd);
		last_pid = child_action(current, input_fd, output_fd);
		if (input_fd != STDIN_FILENO)
			close(input_fd);
		if (output_fd != STDOUT_FILENO)
			close(output_fd);
		input_fd = STDIN_FILENO;
		if (current->next)
			input_fd = pipe_fd[0];
		current = current->next;
	}
	return (wait_for_children(last_pid));
}
