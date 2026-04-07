/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_exec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttiprez <ttiprez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 19:50:19 by ttiprez           #+#    #+#             */
/*   Updated: 2026/04/07 15:48:51 by ttiprez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	cmd_not_found(char *cmd)
{
	ft_putstr_fd(cmd, 2);
	ft_putendl_fd(": command not found", 2);
}

void	close_all_fd(void)
{
	int	fd;

	fd = 3;
	while (fd < 1024)
		close(fd++);
}

//static void	exec_command(t_lstcmd *lst, t_lstcmd *cmd)
//{
//	if (!cmd->cmd_with_path)
//	{
//		cmd_not_found(cmd->cmd_split[0]);
//		free_lstcmd(lst);
//		exit(CMD_NOT_FOUND);
//	}
//	execve(cmd->cmd_with_path, cmd->cmd_split, cmd->envp);
//	perror(cmd->cmd_split[0]);
//	free_lstcmd(lst);
//	return (exit(CMD_EXEC_ERROR));
//}

//int	child_action(t_lstcmd *lst, t_lstcmd *cmd, int from, int to)
//{
//	pid_t	child;

//	if (from < 0)
//	{
//		if (to >= 0)
//			close(to);
//		return (0);
//	}
//	child = fork();
//	if (child == -1)
//		return (close(from), close(to), perror("fork()"), false);
//	if (child == 0)
//	{
//		if (dup2(from, STDIN_FILENO) == -1)
//			return (free_lstcmd(lst), exit(EXIT_FAILURE), -1);
//		if (dup2(to, STDOUT_FILENO) == -1)
//			return (free_lstcmd(lst), exit(EXIT_FAILURE), -1);
//		close(to);
//		close(from);
//		close_all_fd();
//		exec_command(lst, cmd);
//	}
//	return (close(from), close(to), child);
//}
