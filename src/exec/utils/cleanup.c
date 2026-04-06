/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttiprez <ttiprez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 19:52:29 by ttiprez           #+#    #+#             */
/*   Updated: 2026/04/03 17:43:10 by ttiprez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_split(char **splitted_words)
{
	int	i;

	i = -1;
	while (splitted_words[++i])
		free(splitted_words[i]);
	free(splitted_words);
}

void	cleanup(t_lstcmd *lst, int fd_in, int fd_out)
{
	if (lst)
		free_lstcmd(lst);
	if (fd_in >= 0)
		close(fd_in);
	if (fd_out >= 0)
		close(fd_out);
}
