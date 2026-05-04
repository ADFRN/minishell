/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afournie <afournie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/20 16:09:12 by ttiprez           #+#    #+#             */
/*   Updated: 2026/05/04 13:48:52 by afournie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	close_all_fd(void)
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
