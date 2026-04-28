/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttiprez <ttiprez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/17 13:40:56 by ttiprez           #+#    #+#             */
/*   Updated: 2026/04/28 16:00:20 by ttiprez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	wait_for_children(pid_t last_pid)
{
	int		status;
	int		exit_code;
	pid_t	pid;

	free((exit_code = 0, pid = waitpid(-1, &status, 0), NULL));
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
			else if (WIFEXITED(status))
				exit_code = WEXITSTATUS(status);
		}
		pid = waitpid(-1, &status, 0);
	}
	return (exit_code);
}

bool	is_builtins(t_cmd *cmd)
{
	if (!cmd->args[0])
		return (false);
	return (!ft_strcmp(cmd->args[0], EXIT) || !ft_strcmp(cmd->args[0], ECHO)
		|| !ft_strcmp(cmd->args[0], PWD) || !ft_strcmp(cmd->args[0], ENV)
		|| !ft_strcmp(cmd->args[0], EXPORT) || !ft_strcmp(cmd->args[0], CD)
		|| !ft_strcmp(cmd->args[0], UNSET));
}

void	cmd_not_found(char *cmd)
{
	ft_putstr_fd(cmd, 2);
	ft_putendl_fd(": command not found", 2);
}

//void	safe_close(int	*fd)
//{
//	if (*fd >= 0)
//	{
//		close(*fd);
//		*fd = -1;
//	}
//}
