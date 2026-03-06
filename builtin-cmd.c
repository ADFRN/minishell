/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin-cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afournie <afournie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/05 13:25:55 by afournie          #+#    #+#             */
/*   Updated: 2026/03/06 17:22:46 by afournie         ###   ########.fr       */
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

void	cd_cmd(char *s)
{
	char	*path;
	char	*dest;
	char	*absolute_path;

	if (is_absolute_path(s))
	{
		printf("if");
		if (chdir(s) == -1)
			perror("Error :");
	}
	else
	{
		dest = ft_strjoin("/", s);
		path = pwd_cmd();
		absolute_path = ft_strjoin(path, dest);
		if (chdir(path) == -1)
			perror("Error :");
	}
}

char	*get_env(char *s, char **envp)
{
	int	i;

	i = -1;
	while (envp[++i])
		if (ft_strncmp(envp[i], s, 5) == 0)
			return (&envp[i][5]);
	return (NULL);
}

// int	main(int ac, char **av, char **envp)
// {
// 	int		i;
// 	char	**envcpy;

// 	i = 0;
// 	envcpy = env_cpy(envp);
// 	while (envp[i])
// 	{
// 		printf("%d: %s\n", i, envp[i]);
// 		i++;
// 	}
// 	return (0);
// }
