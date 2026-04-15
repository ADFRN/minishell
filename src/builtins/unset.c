/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afournie <afournie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/15 15:59:55 by afournie          #+#    #+#             */
/*   Updated: 2026/04/15 16:06:17 by afournie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exec_unset(t_cmd *cmd, char ***env_ptr)
{
	int		arg_idx;
	int		env_idx;
	char	**env;

	if (!cmd->args[1] || !env_ptr || !*env_ptr)
		return ;
	arg_idx = 1;
	while (cmd->args[arg_idx])
	{
		env = *env_ptr;
		env_idx = get_env_i(env, cmd->args[arg_idx]);
		if (env_idx != -1)
		{
			free(env[env_idx]);
			while (env[env_idx])
			{
				env[env_idx] = env[env_idx + 1];
				env_idx++;
			}
		}
		arg_idx++;
	}
}
