/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttiprez <ttiprez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/09 11:58:18 by ttiprez           #+#    #+#             */
/*   Updated: 2026/04/24 17:42:25 by ttiprez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	exec_solo_builtin(t_mini *mini, t_cmd *cmd)
{
	int	saved_stdin;
	int	saved_stdout;
	int	exit_status;

	saved_stdin = dup(STDIN_FILENO);
	saved_stdout = dup(STDOUT_FILENO);
	if (open_files(&cmd->redir))
	{
		exec_builtins(mini, cmd);
		exit_status = 0;
	}
	else
		exit_status = 1;
	dup2(saved_stdin, STDIN_FILENO);
	dup2(saved_stdout, STDOUT_FILENO);
	safe_close(&saved_stdin);
	safe_close(&saved_stdout);
	return (exit_status);
}

int	pipex(t_mini *mini)
{
	t_cmd	*c_cmds;
	int		pipe_fd[2];
	int		input_fd;
	int		last_pid;

	c_cmds = mini->cmds;
	input_fd = -1;
	last_pid = 0;
	if (is_builtins(c_cmds) && !c_cmds->next)
		return (exec_solo_builtin(mini, c_cmds));
	while (c_cmds)
	{
		free((pipe_fd[0] = -1, pipe_fd[1] = -1, NULL));
		if (c_cmds->next && pipe(pipe_fd) == -1)
			exit((perror("pipe"), cleaning(&mini->env), EXIT_FAILURE));
		last_pid = child_action(mini, c_cmds, input_fd, pipe_fd);
		free((safe_close(&input_fd), safe_close(&pipe_fd[1]), NULL));
		input_fd = pipe_fd[0];
		c_cmds = c_cmds->next;
	}
	safe_close(&input_fd);
	return (wait_for_children(last_pid));
}
