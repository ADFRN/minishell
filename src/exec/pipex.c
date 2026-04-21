/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttiprez <ttiprez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/09 11:58:18 by ttiprez           #+#    #+#             */
/*   Updated: 2026/04/21 15:58:02 by ttiprez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	{
		exec_builtins(current);
		return (last_pid);
	}
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
