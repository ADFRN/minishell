/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_exec.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttiprez <ttiprez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/17 13:35:05 by ttiprez           #+#    #+#             */
/*   Updated: 2026/04/21 16:58:37 by ttiprez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	ft_isnumber(char *str)
{
	int	i;

	i = -1;
	if (!ft_isdigit(str[++i]) && str[i] != '-' && str[i] != '+')
		return (false);
	while (str[++i])
		if (!ft_isdigit(str[i]))
			return (false);
	return (true);
}

static void	exec_exit(t_cmd *cmd)
{
	if (!cmd->next)
		ft_putendl_fd("exit", STDIN_FILENO);
	if (cmd->args[1] && ft_isnumber(cmd->args[1]) && cmd->args[2])
		ft_putendl_fd("bash: exit: too many arguments", STDERR_FILENO);
	else if (cmd->args[1] && !ft_isnumber(cmd->args[1]))
	{
		ft_putstr_fd("bash: exit: ", STDERR_FILENO);
		ft_putstr_fd(cmd->args[1], STDERR_FILENO);
		ft_putendl_fd(": numeric argument required", STDERR_FILENO);
		exit((cleaning(cmd->envp), 2));
	}
	else if (!cmd->args[1])
		exit((cleaning(cmd->envp), 0));
	else
		exit((cleaning(cmd->envp), ft_atoi(cmd->args[1])));
}

void	exec_builtins(t_cmd *cmd)
{
	if (!ft_strcmp(cmd->args[0], CD))
		exec_cd(cmd);
	else if (!ft_strcmp(cmd->args[0], ECHO))
		exec_echo(cmd);	
	else if (!ft_strcmp(cmd->args[0], ENV))
		exec_env(cmd);
	else if (!ft_strcmp(cmd->args[0], PWD))
		exec_pwd();
	else if (!ft_strcmp(cmd->args[0], EXPORT))
		exec_export(cmd, cmd->envp);
	else if (!ft_strcmp(cmd->args[0], UNSET))
		exec_unset(cmd, &cmd->envp);
	else if (!ft_strcmp(cmd->args[0], EXIT))
		exec_exit(cmd);
}
