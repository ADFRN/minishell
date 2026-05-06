/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afournie <afournie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/10 15:10:50 by afournie          #+#    #+#             */
/*   Updated: 2026/05/06 13:57:01 by afournie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	ft_has_option(t_cmd *cmd)
{
	int	i;

	if (cmd->args[1] && cmd->args[1][0] == '-' && cmd->args[1][1] == 'n')
	{
		i = 1;
		while (cmd->args[1][i])
		{
			if (cmd->args[1][i] != 'n')
				return (false);
			i++;
		}
		return (true);
	}
	return (false);
}

int	exec_echo(t_cmd *cmd)
{
	bool	has_option;
	int		i;

	i = 1;
	has_option = ft_has_option(cmd);
	while (cmd->args[i + has_option])
	{
		printf("%s", cmd->args[i + has_option]);
		if (cmd->args[i + has_option + 1])
			printf(" ");
		i++;
	}
	if (!has_option)
		printf("\n");
	return (EXIT_SUCCESS);
}
