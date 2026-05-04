/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttiprez <ttiprez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/27 19:39:30 by ttiprez           #+#    #+#             */
/*   Updated: 2026/05/04 14:44:43 by ttiprez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*exec_pwd(t_env **env)
{
	char	tmp[PATH_MAX];
	char	*path;

	if (getcwd(tmp, PATH_MAX) != NULL)
	{
		path = ft_strdup(tmp);
		if (!path)
			exit((cleaning(env), EXIT_FAILURE));
		return (path);
	}
	return (NULL);
}
