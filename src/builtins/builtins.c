/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttiprez <ttiprez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/05 13:25:55 by afournie          #+#    #+#             */
/*   Updated: 2026/04/20 15:06:00 by ttiprez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exec_env(t_cmd *cmd)
{
	int	i;

	i = 0;
	while (cmd->envp[i])
	{
		if (ft_strncmp(cmd->envp[i], "=", ft_strlen(cmd->envp[i])))
			printf("%s\n", cmd->envp[i]);
		i++;
	}
}

char	*exec_pwd(void)
{
	char	tmp[PATH_MAX];
	char	*path;

	printf("getcwd = %s\n", getcwd(tmp, PATH_MAX));
	printf("tmp = %s\n", tmp);
	if (getcwd(tmp, PATH_MAX) != NULL)
	{
		path = ft_strdup(tmp);
		if (!path)
			return (NULL);
		return (path);
	}
	return (perror("minishell: pwd"), NULL);
}
