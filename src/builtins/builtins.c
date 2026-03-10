/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afournie <afournie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/05 13:25:55 by afournie          #+#    #+#             */
/*   Updated: 2026/03/10 15:39:12 by afournie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	echo_cmd(char *s)
{
	printf("%s", s);
}

void	env_cmd(char **envcpy)
{
	int	i;
	int	j;

	i = 0;
	j = count_env_vars(envcpy);
	while (i < j)
	{
		printf("%s\n", envcpy[i]);
		i++;
	}
}

char	*pwd_cmd(void)
{
	char	tmp[PATH_MAX];
	char	*path;

	if (getcwd(tmp, PATH_MAX) != NULL)
	{
		path = ft_strdup(tmp);
		if (!path)
			return (NULL);
		return (path);
	}
	else
	{
		perror("minishell: pwd");
		return (NULL);
	}
}

void	cd_cmd(char *s, char **envcpy)
{
	int		oldpwd_id;
	int		pwd_id;
	char	*current_dir;

	oldpwd_id = get_env_i(envcpy, "OLDPWD");
	pwd_id = get_env_i(envcpy, "PWD");
	current_dir = pwd_cmd();
	if (chdir(s) == -1)
		perror("Error :");
	else
	{
		envcpy[oldpwd_id] = ft_strjoin("OLDPWD=", current_dir);
		envcpy[pwd_id] = ft_strjoin("PWD=", pwd_cmd());
	}
}

void	export_cmd(char *var_name, char *var_value, char **envcpy)
{
	char	*new_value;
	char	*tmp;
	int		i;

	tmp = add_equal(var_value);
	new_value = ft_strjoin(var_name, tmp);
	free(tmp);
	i = count_env_vars(envcpy);
	envcpy[i] = new_value;
	envcpy[i + 1] = NULL;
}

void	unset_cmd(char *var_name, char **envcpy)
{
	int		i;
	int		found;
	size_t	len;

	i = 0;
	found = 0;
	len = ft_strlen(var_name);
	while (envcpy[i])
	{
		if (ft_strncmp(envcpy[i], var_name, len) == 0 && envcpy[i][len] == '=')
		{
			free(envcpy[i]);
			while (envcpy[i])
			{
				envcpy[i] = envcpy[i + 1];
				i++;
			}
			return ;
		}
		i++;
	}
}
