/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttiprez <ttiprez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/10 15:10:50 by afournie          #+#    #+#             */
/*   Updated: 2026/04/21 17:05:15 by ttiprez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exec_echo(t_cmd *cmd)
{
	bool	has_option;
	int		i;

	i = 1;
	if (!cmd->args[1])
		has_option = false;
	else
		has_option = !ft_strcmp(cmd->args[1], "-n");
	while (cmd->args[i + has_option])
	{
		printf("%s", cmd->args[i + has_option]);
		if (cmd->args[i + has_option + 1])
			printf(" ");
		i++;
	}
	if (!has_option)
		printf("\n");
}
