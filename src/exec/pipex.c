/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttiprez <ttiprez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/09 11:58:18 by ttiprez           #+#    #+#             */
/*   Updated: 2026/04/21 16:53:15 by ttiprez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	exec_solo_builtin(t_cmd *cmd)
{
	int	saved_stdin;
	int	saved_stdout;
	int	exit_status;

	saved_stdin = dup(STDIN_FILENO);
	saved_stdout = dup(STDOUT_FILENO);
	if (open_files(&cmd->redir))
	{
		exec_builtins(cmd);
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

int	pipex(t_cmd **lst_cmd)
{
	t_cmd	*current;
	int		pipe_fd[2];
	int		input_fd;
	int		last_pid;

	current = *lst_cmd;
	input_fd = -1;
	last_pid = 0;
	if (is_builtins(current) && !current->next)
		return (exec_solo_builtin(current));
	while (current)
	{
		free((pipe_fd[0] = -1, pipe_fd[1] = -1, NULL));
		if (current->next && pipe(pipe_fd) == -1)
			exit((perror("pipe"), cleaning(current->envp), EXIT_FAILURE));
		last_pid = child_action(current, input_fd, pipe_fd);
		free((safe_close(&input_fd), safe_close(&pipe_fd[1]), NULL));
		input_fd = pipe_fd[0];
		current = current->next;
	}
	safe_close(&input_fd);
	return (wait_for_children(last_pid));
}
