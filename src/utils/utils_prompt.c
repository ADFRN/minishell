/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_prompt.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afournie <afournie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/27 15:00:28 by afournie          #+#    #+#             */
/*   Updated: 2026/03/27 15:10:39 by afournie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*get_hostname(void)
{
	int		fd;
	char	*buf;
	int		n;
	int		i;

	buf = malloc(256);
	if (!buf)
		return (NULL);
	fd = open("/etc/hostname", O_RDONLY);
	if (fd == -1)
		return (free(buf), NULL);
	n = read(fd, buf, 255);
	close(fd);
	if (n <= 0)
		return (free(buf), NULL);
	buf[n] = '\0';
	i = 0;
	while (buf[i] && buf[i] != '.' && buf[i] != '\n')
		i++;
	buf[i] = '\0';
	return (buf);
}

static char	*get_current_dir(void)
{
	char	*cwd;
	char	*home;
	char	*result;
	size_t	home_len;

	cwd = getcwd(NULL, 0);
	home = getenv("HOME");
	if (!cwd || !home)
		return (cwd);
	home_len = ft_strlen(home);
	if (ft_strncmp(cwd, home, home_len) == 0
		&& (cwd[home_len] == '/' || cwd[home_len] == '\0'))
	{
		result = malloc(ft_strlen(cwd) - home_len + 2);
		result[0] = '~';
		ft_strcpy(result + 1, cwd + home_len);
		free(cwd);
		return (result);
	}
	return (cwd);
}

char	*create_prompt_line(void)
{
	char	*prompt;
	char	*username;
	char	*hostname;
	char	*current_dirrectory;

	prompt = ft_strjoin(getenv("USER"), "@");
	prompt = ft_strjoin(prompt, get_hostname());
	prompt = ft_strjoin(prompt, ":");
	prompt = ft_strjoin(prompt, get_current_dir());
	prompt = ft_strjoin(prompt, "$ ");
	return (prompt);
}
