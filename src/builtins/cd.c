/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttiprez <ttiprez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/10 15:04:04 by afournie          #+#    #+#             */
/*   Updated: 2026/04/20 16:16:27 by ttiprez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	update_env_var(t_cmd *cmd, int index, char *name, char *value)
{
	char	*new_var;
	int		i;
	int		j;

	if (index == -1)
		return ;
	new_var = malloc(sizeof(char) * (ft_strlen(name) + ft_strlen(value) + 1));
	if (!new_var)
		return ;
	i = -1;
	while (name[++i])
		new_var[i] = name[i];
	j = -1;
	while (value[++j])
		new_var[i + j] = value[j];
	new_var[i + j] = '\0';
	free(cmd->envp[index]);
	cmd->envp[index] = new_var;
}

static int	cd(t_cmd *cmd, int oldpwd_id, int pwd_id, char *current_dir)
{
	char	*error_msg;

	if (chdir(cmd->args[1]) == -1)
	{
		error_msg = ft_strjoin("Minishell: cd: ", cmd->args[1]);
		perror(error_msg);
		return (EXIT_FAILURE);
	}
	else
	{
		update_env_var(cmd, oldpwd_id, "OLDPWD=", current_dir);
		update_env_var(cmd, pwd_id, "PWD=", exec_pwd());
		return (EXIT_SUCCESS);
	}
}

static int	back_home(t_cmd *cmd, int oldpwd_id, int pwd_id, char *current_dir)
{
	int		home_id;
	char	*home_char;
	char	*error_msg;
	char	*tmp;

	home_id = get_env_i(cmd->envp, "HOME");
	if (home_id == -1)
	{
		printf("Minishell: cd: HOME not set\n");
		return (EXIT_FAILURE);
	}
	tmp = ft_strchr(cmd->envp[home_id], '=');
	home_char = ft_strdup(tmp + 1);
	if (chdir(home_char) == -1)
	{
		error_msg = ft_strjoin("Minishell: cd: ", home_char);
		perror(error_msg);
		return (EXIT_FAILURE);
	}
	else
	{
		update_env_var(cmd, oldpwd_id, "OLDPWD=", current_dir);
		update_env_var(cmd, pwd_id, "PWD=", exec_pwd());
		return (EXIT_SUCCESS);
	}
}

int	exec_cd(t_cmd *cmd)
{
	int		oldpwd_id;
	int		pwd_id;
	char	*current_dir;

	oldpwd_id = get_env_i(cmd->envp, "OLDPWD");
	pwd_id = get_env_i(cmd->envp, "PWD");
	current_dir = exec_pwd();
	if (cmd->args[1])
		return (cd(cmd, oldpwd_id, pwd_id, current_dir));
	else
		return (back_home(cmd, oldpwd_id, pwd_id, current_dir));
}
