/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afournie <afournie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/15 11:55:47 by afournie          #+#    #+#             */
/*   Updated: 2026/04/15 15:49:55 by afournie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	print_export(char **env)
{
	int	i;

	i = -1;
	while (env[++i])
		printf("export %s\n", env[i]);
}

static void	add_var(char *s, char ***env)
{
	char	*ptr;
	char	*key;
	int		env_index;

	ptr = ft_strchr(s, '=');
	if (ptr)
		key = ft_substr(s, 0, ptr - s);
	else
		key = ft_strdup(s);
	env_index = get_env_i(*env, key);
	if (env_index != -1)
	{
		if (ptr)
		{
			free((*env)[env_index]);
			(*env)[env_index] = ft_strdup_classic(s);
		}
	}
	else
		realloc_env(env, s);
}

void	exec_export(t_cmd *cmd, char ***envcpy)
{
	int	i;

	if (cmd->args[1])
	{
		i = 0;
		while (cmd->args[++i])
			add_var(cmd->args[i], envcpy);
	}
	else
		print_export(*envcpy);
}
