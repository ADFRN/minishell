/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_exec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttiprez <ttiprez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 19:50:19 by ttiprez           #+#    #+#             */
/*   Updated: 2026/04/17 13:47:08 by ttiprez          ###   ########.fr       */
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
	reset_signals_child();
	if (dup2(from, STDIN_FILENO) == -1 || dup2(to, STDOUT_FILENO) == -1)
		exit(EXIT_FAILURE);
	if (!open_files(&cmd->redir))
		exit(EXIT_FAILURE);
	if (is_builtins(cmd))
		exec_builtins(cmd);
	else if (cmd->args && cmd->args[0])
		exec_cmd(cmd);
	exit(EXIT_FAILURE);
}

int	child_action(t_cmd *cmd, int from, int to)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		exit((perror("fork"), \
			close_all_fd(), free_env(cmd->envp), ft_free(), EXIT_FAILURE));
	if (pid == 0)
		child_process(cmd, from, to);
	return (pid);
}
