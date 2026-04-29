/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_exec.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttiprez <ttiprez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/17 13:35:05 by ttiprez           #+#    #+#             */
/*   Updated: 2026/04/29 16:57:42 by ttiprez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exec_builtins(t_mini *mini, t_cmd *cmd)
{
	char	*pwd_result;

	if (!ft_strcmp(cmd->args[0], CD))
		return (exec_cd(cmd, &mini->env));
	else if (!ft_strcmp(cmd->args[0], ECHO))
		return (exec_echo(cmd));
	else if (!ft_strcmp(cmd->args[0], ENV))
		return (exec_env(mini->env));
	else if (!ft_strcmp(cmd->args[0], PWD))
	{
		pwd_result = exec_pwd();
		if (!pwd_result)
			return (perror("Minishelle: pwd : error retrieving current \
directory: getcwd: cannot access parent directories"), EXIT_FAILURE);
		return (printf("%s\n", pwd_result), EXIT_SUCCESS);
	}
	else if (!ft_strcmp(cmd->args[0], EXPORT))
		return (exec_export(cmd, &mini->env));
	else if (!ft_strcmp(cmd->args[0], UNSET))
		return (exec_unset(cmd, &mini->env));
	else if (!ft_strcmp(cmd->args[0], EXIT))
		return (exec_exit(cmd, &mini->env));
	else
		return (-1);
}
