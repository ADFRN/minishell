/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afournie <afournie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/10 15:04:04 by afournie          #+#    #+#             */
/*   Updated: 2026/04/10 15:04:40 by afournie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
