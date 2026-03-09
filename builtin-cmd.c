/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin-cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afournie <afournie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/05 13:25:55 by afournie          #+#    #+#             */
/*   Updated: 2026/03/09 12:23:10 by afournie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

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
	test = get_env("OLDPWD", envcpy);
	oldpwd_id = get_env_i("OLDPWD", envcpy);
	pwd_id = get_env_i("PWD", envcpy);
	current_dir = pwd_cmd();
	if (chdir(s) == -1)
		perror("Error :");
	else
	{
		envcpy[oldpwd_id] = current_dir;
		envcpy[pwd_id] = pwd_cmd();
	}
}

char	*get_env(char *s, char **envcpy)
{
	int	i;

	i = -1;
	while (envcpy[++i])
		if (ft_strncmp(envcpy[i], s, ft_strlen(s)) == 0)
			return (&envcpy[i][ft_strlen(s)]);
	return (NULL);
}

int	get_env_i(char *s, char **envcpy)
{
	int	i;

	i = -1;
	while (envcpy[++i])
		if (ft_strncmp(envcpy[i], s, ft_strlen(s)) == 0)
			return (i);
	return (-1);
}

int	suitebordel(int ac, char **av, char **envcpy)
{
	(void)envcpy;
	(void)ac;
	(void)av;
	return (0);
}
