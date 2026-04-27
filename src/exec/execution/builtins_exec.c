/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_exec.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttiprez <ttiprez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/17 13:35:05 by ttiprez           #+#    #+#             */
/*   Updated: 2026/04/27 19:46:01 by ttiprez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exec_builtins(t_mini *mini, t_cmd *cmd)
{
	if (!ft_strcmp(cmd->args[0], CD))
		return (exec_cd(cmd, &mini->env));
	else if (!ft_strcmp(cmd->args[0], ECHO))
		return (exec_echo(cmd));	
	else if (!ft_strcmp(cmd->args[0], ENV))
		return (exec_env(mini->env));
	else if (!ft_strcmp(cmd->args[0], PWD))
		return (exec_pwd(), EXIT_SUCCESS);
	else if (!ft_strcmp(cmd->args[0], EXPORT))
		return (exec_export(cmd, &mini->env));
	else if (!ft_strcmp(cmd->args[0], UNSET))
		return (exec_unset(cmd, &mini->env));
	else if (!ft_strcmp(cmd->args[0], EXIT))
		return (exec_exit(cmd, &mini->env));
	else
		return (-1);
}
