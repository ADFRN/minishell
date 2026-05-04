/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttiprez <ttiprez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/10 15:04:04 by afournie          #+#    #+#             */
/*   Updated: 2026/05/04 14:23:48 by ttiprez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	cd(t_cmd *cmd, t_env **env, char *current_dir)
{
	if (ft_strcmp(cmd->args[1], "-") == 0 && chdir(ft_env_get_val(*env,
				"OLDPWD")) == 0)
	{
		ft_env_update(env, "OLDPWD", current_dir);
		ft_env_update(env, "PWD", exec_pwd());
		printf("%s\n", ft_env_get_val(*env, "PWD"));
		return (EXIT_SUCCESS);
	}
	else if (chdir(cmd->args[1]) == 0)
	{
		ft_env_update(env, "OLDPWD", current_dir);
		ft_env_update(env, "PWD", exec_pwd());
		return (EXIT_SUCCESS);
	}
	else
	{
		write(STDERR_FILENO, "Minishell: cd: ", 15);
		if (ft_strcmp(cmd->args[1], "-") == 0 && !ft_env_get_val(*env,
				"OLDPWD"))
			ft_putendl_fd("OLDPWD not set", STDERR_FILENO);
		else
			perror(cmd->args[1]);
		return (EXIT_FAILURE);
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
		ft_env_update(env, "OLDPWD", current_dir);
		write(STDOUT_FILENO, "Minishell: cd: ", 15);
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

	if (cmd->args[1] && cmd->args[2])
		return (ft_putendl_fd("Minishell: cd: too many arguments",
				STDERR_FILENO), EXIT_FAILURE);
	current_dir = exec_pwd();
	if (cmd->args[1])
		return (cd(cmd, env, current_dir));
	else
		return (back_home(env, current_dir));
}
