/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afournie <afournie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/09 11:58:18 by ttiprez           #+#    #+#             */
/*   Updated: 2026/04/30 17:28:29 by afournie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	exec_solo_builtin(t_mini *mini, t_cmd *cmd)
{
	int	exit_status;

	exit_status = EXIT_FAILURE;
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
		pipe_fd[0] = -1;
		pipe_fd[1] = -1;
		if (c_cmds->next && pipe(pipe_fd) == -1)
			exit((perror("pipe"), cleaning(&mini->env), EXIT_FAILURE));
		last_pid = child_action(mini, c_cmds, input_fd, pipe_fd);
		if (pipe_fd[1] != -1)
			close(pipe_fd[1]);
		if (input_fd != -1)
			close(input_fd);
		input_fd = pipe_fd[0];
		c_cmds = c_cmds->next;
	}
	return (wait_for_children(last_pid));
}
