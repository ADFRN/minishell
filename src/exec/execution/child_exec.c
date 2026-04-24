/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_exec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttiprez <ttiprez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 19:50:19 by ttiprez           #+#    #+#             */
/*   Updated: 2026/04/24 18:32:38 by ttiprez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void exit_child(t_mini *mini)
{
	cleaning(&mini->env);
	close(STDIN_FILENO);
	close(STDOUT_FILENO);
	close(STDERR_FILENO);
	exit(mini->last_exit);
}

static void	exec_cmd(t_mini *mini, t_cmd *cmd)
{
	if (!cmd->cmd_with_path)
	{
		cmd_not_found(cmd->args[0]);
		exit_child((mini->last_exit = CMD_NOT_FOUND, mini));
	}
	execve(cmd->cmd_with_path, cmd->args, env_to_char_tab(mini->env));
	perror(cmd->args[0]);
	exit_child((mini->last_exit = CMD_EXEC_ERROR, mini));
}

static void	child_process(t_mini *mini, t_cmd *cmd, int input_fd, int pipe_fd[2])
{
	reset_signals_child();
	safe_close(&pipe_fd[0]);
	if (input_fd != -1)
	{
		if (dup2(input_fd, STDIN_FILENO) == -1)
			exit((cleaning(&mini->env), EXIT_FAILURE));
		safe_close(&input_fd);
	}
	if (pipe_fd[1] != -1)
	{
		if (dup2(pipe_fd[1], STDOUT_FILENO) == -1)
			exit((cleaning(&mini->env), EXIT_FAILURE));
		safe_close(&pipe_fd[1]);
	}
	if (!open_files(&cmd->redir))
		exit_child((mini->last_exit = EXIT_FAILURE, mini));
	if (is_builtins(cmd))
	{
		exec_builtins(mini, cmd);
		exit_child((mini->last_exit = EXIT_SUCCESS, mini));
	}
	else if (cmd->args && cmd->args[0])
		exec_cmd(mini, cmd);
	exit_child((mini->last_exit = EXIT_SUCCESS, mini));
}

int	child_action(t_mini *mini, t_cmd *cmd,int input_fd, int pipe_fd[2])
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		exit((perror("fork"), cleaning(&mini->env), EXIT_FAILURE));
	if (pid == 0)
		child_process(mini, cmd, input_fd, pipe_fd);
	return (pid);
}
