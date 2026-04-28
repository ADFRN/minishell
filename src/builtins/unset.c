/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttiprez <ttiprez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/15 15:59:55 by afournie          #+#    #+#             */
/*   Updated: 2026/04/28 14:44:30 by ttiprez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exec_unset(t_cmd *cmd, t_env **env)
{
	int		i;

	if (!cmd->args[1] || !env)
		return (0);
	i = 0;
	while (cmd->args[++i])
		ft_env_remove(env, cmd->args[i]);
	return (0);
}
