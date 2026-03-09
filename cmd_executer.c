/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_executer.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afournie <afournie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/12 14:02:17 by ttiprez           #+#    #+#             */
/*   Updated: 2026/03/09 11:14:12 by afournie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

void	exec_cmd(char *rl)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (rl[i])
	{
		if (i == 0 && rl[i] == 'p')
			j++;
		if (i == 1 && rl[i] == 'w')
			j++;
		if (i == 2 && rl[i] == 'd')
			j++;
		i++;
	}
	if (j == 3)
		printf("pwd:%s\n", getcwd(NULL, 0));
}
