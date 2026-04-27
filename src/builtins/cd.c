/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttiprez <ttiprez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/10 15:04:04 by afournie          #+#    #+#             */
/*   Updated: 2026/04/27 19:45:01 by ttiprez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	cd(t_cmd *cmd, t_env **env, char *current_dir)
{
	if (chdir(cmd->args[1]) == -1)
	{
		printf("Minishell: cd: ");
		perror(cmd->args[1]);
		return (EXIT_FAILURE);
	}
	else
	{
		ft_env_update(env, "OLDPWD", current_dir);
		ft_env_update(env, "PWD", exec_pwd());
		return (EXIT_SUCCESS);
	}
}

static int	back_home(t_env **env, char *current_dir)
{
	char	*home_value;

	home_value = ft_env_get_val(*env, "HOME");
	if (!home_value)
		return (printf("Minishell: cd: HOME not set\n"), EXIT_FAILURE);
	if (chdir(home_value) == -1)
	{
		printf("Minishell: cd: ");
		perror(home_value);
		return (EXIT_FAILURE);
	}
	else
	{
		ft_env_update(env, "OLDPWD", current_dir);
		ft_env_update(env, "PWD", exec_pwd());
		return (EXIT_SUCCESS);
	}
}

int	exec_cd(t_cmd *cmd, t_env **env)
{
	char	*current_dir;

	current_dir = exec_pwd();
	if (cmd->args[1])
		return (cd(cmd, env, current_dir));
	else
		return (back_home(env, current_dir));
}
