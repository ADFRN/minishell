/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afournie <afournie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/15 11:55:47 by afournie          #+#    #+#             */
/*   Updated: 2026/04/27 12:40:27 by afournie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	add_var(char *s, t_env **env)
{
	char	*key;
	char	*value;
	char	*sep;

	if (!parse_kv(s, &key, &value, &sep))
		return (false);
	if (update_var(*env, key, value, sep))
		return (true);
	if (!create_var(env, key, value))
		return (false);
	return (true);
}

int	exec_export(t_cmd *cmd, t_env **env)
{
	int	i;
	int	exit_value;

	exit_value = 0;
	if (cmd->args[1])
	{
		i = 0;
		while (cmd->args[++i])
		{
			if (!is_valid_args(cmd->args[i]))
			{
				exit_value = 1;
				printf("Minishell: export: `%s\':not a valid identifier\n",
					cmd->args[i]);
				continue ;
			}
			if (!add_var(cmd->args[i], env))
				exit((ft_free(), ft_env_free(env), EXIT_FAILURE));
		}
	}
	else
		print_export(*env);
	return (exit_value);
}
