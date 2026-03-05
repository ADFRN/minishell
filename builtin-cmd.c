/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin-cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afournie <afournie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/05 13:25:55 by afournie          #+#    #+#             */
/*   Updated: 2026/03/05 16:12:09 by afournie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <errno.h>
#include <linux/limits.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int	ft_strlen(const char *s)
{
	int	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

char	*ft_strdup(const char *s)
{
	int		i;
	int		size;
	char	*new;

	i = 0;
	size = ft_strlen(s);
	new = malloc(sizeof(char) * (size + 1));
	if (!new)
		return (NULL);
	while (s[i])
	{
		new[i] = s[i];
		i++;
	}
	new[i] = '\0';
	return (new);
}

char	*ft_strjoin(const char *s1, const char *s2)
{
	int		len;
	char	*new;
	int		i;
	int		j;

	if (!s1 || !s2)
		return (NULL);
	i = -1;
	j = 0;
	len = (ft_strlen(s1) + ft_strlen(s2));
	new = malloc(sizeof(char) * (len + 1));
	if (!new)
		return (NULL);
	while (s1[++i])
		new[i] = s1[i];
	while (s2[j])
	{
		new[i] = s2[j];
		i++;
		j++;
	}
	new[i] = '\0';
	return (new);
}

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
		printf("absolute_path: %s\n", absolute_path);
		if (chdir(path) == -1)
			perror("Error :");
	}
}

int	main(int ac, char **av)
{
	printf("%s", pwd_cmd());
	cd_cmd(av[1]);
	return (0);
}
