/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_exec.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttiprez <ttiprez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 19:49:01 by ttiprez           #+#    #+#             */
/*   Updated: 2026/04/15 14:50:24 by ttiprez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	wait_for_children(pid_t last_pid)
{
	int		status;
	int		exit_code;
	pid_t	pid;

	exit_code = 0;
	pid = wait(&status);
	while (pid > 0)
	{
		if (pid == last_pid)
		{
			if (WIFSIGNALED(status))
			{
				exit_code = 128 + WTERMSIG(status);
				if (WTERMSIG(status) == SIGINT)
					write(1, "\n", 1);
				else if (WTERMSIG(status) == SIGQUIT)
					write(1, "Quit (core dumped)\n", 19);
			}
			else
				exit_code = WEXITSTATUS(status);
		}
		pid = wait(&status);
	}
	return (exit_code);
}
