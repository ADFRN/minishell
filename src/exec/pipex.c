/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttiprez <ttiprez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/09 11:58:18 by ttiprez           #+#    #+#             */
/*   Updated: 2026/04/28 16:08:32 by ttiprez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	exec_solo_builtin(t_mini *mini, t_cmd *cmd)
{
	int	exit_status;

	if (open_files(&cmd->redir))
	{
		if (!ft_strcmp(cmd->args[0], "exit"))
			delete_heredocs_files(&mini->cmds);
		exit_status = exec_builtins(mini, cmd);
	}
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
		//free((safe_close(&input_fd), safe_close(&pipe_fd[1]), NULL));
		input_fd = pipe_fd[0];
		c_cmds = c_cmds->next;
	}
	//safe_close(&input_fd);
	return (wait_for_children(last_pid));
}
