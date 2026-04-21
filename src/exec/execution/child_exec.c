/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_exec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttiprez <ttiprez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 19:50:19 by ttiprez           #+#    #+#             */
/*   Updated: 2026/04/21 16:50:37 by ttiprez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void exit_child(t_cmd *cmd, int exit_code)
{
	cleaning(cmd->envp);
	close(STDIN_FILENO);
	close(STDOUT_FILENO);
	close(STDERR_FILENO);
	exit(exit_code);
}

static void	exec_cmd(t_cmd *cmd)
{
	if (!cmd->cmd_with_path)
	{
		cmd_not_found(cmd->args[0]);
		exit_child(cmd, CMD_NOT_FOUND);
	}
	execve(cmd->cmd_with_path, cmd->args, cmd->envp);
	perror(cmd->args[0]);
	exit_child(cmd, CMD_EXEC_ERROR);
}

static void	child_process(t_cmd *cmd, int input_fd, int pipe_fd[2])
{
	reset_signals_child();
	safe_close(&pipe_fd[0]);
	if (input_fd != -1)
	{
		if (dup2(input_fd, STDIN_FILENO) == -1)
			exit((cleaning(cmd->envp), EXIT_FAILURE));
		safe_close(&input_fd);
	}
	if (pipe_fd[1] != -1)
	{
		if (dup2(pipe_fd[1], STDOUT_FILENO) == -1)
			exit((cleaning(cmd->envp), EXIT_FAILURE));
		safe_close(&pipe_fd[1]);
	}
	if (!open_files(&cmd->redir))
		exit_child(cmd, EXIT_FAILURE);
	if (is_builtins(cmd))
	{
		exec_builtins(cmd);
		exit_child(cmd, EXIT_SUCCESS);
	}
	else if (cmd->args && cmd->args[0])
		exec_cmd(cmd);
	exit_child(cmd, EXIT_SUCCESS);
}

int	child_action(t_cmd *cmd, int input_fd, int pipe_fd[2])
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		exit((perror("fork"), cleaning(cmd->envp), EXIT_FAILURE));
	if (pid == 0)
		child_process(cmd, input_fd, pipe_fd);
	return (pid);
}
