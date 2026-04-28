/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttiprez <ttiprez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/20 16:09:12 by ttiprez           #+#    #+#             */
/*   Updated: 2026/04/28 16:04:00 by ttiprez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	close_all_fd()
{
	int	i;

	i = 3;
	while (i < FD_LIMITS)
		close(i++);
}

void	cleaning(t_env **env)
{
	ft_env_free(env);
	ft_free();
	close_all_fd();
}
