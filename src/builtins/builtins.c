/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttiprez <ttiprez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/05 13:25:55 by afournie          #+#    #+#             */
/*   Updated: 2026/03/09 15:41:12 by ttiprez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	echo_cmd(char *s)
{
	printf("%s", s);
}

bool	is_absolute_path(char *s)
{
	int	i;

	i = 0;
	while (s[i] == ' ')
		i++;
	if (s[i] == '/')
		return (true);
	return (false);
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
		printf("%s\n", path);
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
	char	*test;
	char	*current_dir;

	(void)envcpy;
	test = get_envp(envcpy, "OLDPWD");
	oldpwd_id = get_env_i(envcpy, "OLDPWD");
	pwd_id = get_env_i(envcpy, "PWD");
	current_dir = pwd_cmd();
	if (chdir(s) == -1)
		perror("Error :");
	else
	{
		envcpy[oldpwd_id] = current_dir;
		envcpy[pwd_id] = pwd_cmd();
	}
}

int	suitebordel(int ac, char **av, char **envcpy)
{
	(void)envcpy;
	(void)ac;
	(void)av;
	return (0);
}
