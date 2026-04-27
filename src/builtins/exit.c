/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttiprez <ttiprez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/27 19:29:52 by ttiprez           #+#    #+#             */
/*   Updated: 2026/04/27 19:44:43 by ttiprez          ###   ########.fr       */
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

int		exec_exit(t_cmd *cmd, t_env **env)
{
	if (!cmd->next)
		ft_putendl_fd("exit", STDIN_FILENO);
	if (cmd->args[1] && ft_isnumber(cmd->args[1]) && cmd->args[2])
	{
		ft_putendl_fd("bash: exit: too many arguments", STDERR_FILENO);
		return (EXIT_FAILURE);
	}
	else if (cmd->args[1] && !ft_isnumber(cmd->args[1]))
	{
		ft_putstr_fd("bash: exit: ", STDERR_FILENO);
		ft_putstr_fd(cmd->args[1], STDERR_FILENO);
		ft_putendl_fd(": numeric argument required", STDERR_FILENO);
		exit((cleaning(env), 2));
	}
	else if (!cmd->args[1])
		exit((cleaning(env), EXIT_SUCCESS));
	else
		exit((cleaning(env), ft_atoi(cmd->args[1])));
	return (-1);
}