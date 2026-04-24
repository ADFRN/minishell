/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_parsing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttiprez <ttiprez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 19:36:03 by ttiprez           #+#    #+#             */
/*   Updated: 2026/04/24 17:41:15 by ttiprez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*cat_path_cmd(char *path, char*cmd)
{
	char	*full_cmd;
	char	*tmp;

	full_cmd = ft_strdup(path);
	if (!full_cmd)
		return (NULL);
	tmp = ft_strjoin(full_cmd, "/");
	if (!tmp)
		return (NULL);
	full_cmd = ft_strjoin(tmp, cmd);
	if (!full_cmd)
		return (NULL);
	return (full_cmd);
}

/************************************************************/
/* 			Recupere la commande avec le path				*/
/*	Si la commande a un '/', test avec le chemin litterale	*/
/************************************************************/
char	*get_cmd_with_path(char *cmd, char *path)
{
	char	*full_cmd;
	char	**splitted_path;
	int		i;

	if (ft_strchr(cmd, '/'))
		return (ft_strdup(cmd));
	splitted_path = ft_split(path, ':');
	if (!splitted_path)
		return (NULL);
	i = -1;
	while (splitted_path[++i])
	{
		full_cmd = cat_path_cmd(splitted_path[i], cmd);
		if (!full_cmd)
			return (free_split(splitted_path), NULL);
		if (access(full_cmd, F_OK) == 0)
			return (free_split(splitted_path), full_cmd);
	}
	return (free_split(splitted_path), NULL);
}
