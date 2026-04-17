/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttiprez <ttiprez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/09 11:58:18 by ttiprez           #+#    #+#             */
/*   Updated: 2026/04/17 13:47:04 by ttiprez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
