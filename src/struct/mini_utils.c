/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttiprez <ttiprez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/24 14:23:06 by ttiprez           #+#    #+#             */
/*   Updated: 2026/04/24 14:44:15 by ttiprez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_mini	ft_mini_new(void)
{
	t_mini	mini;

	mini.env = NULL;
	mini.cmds = NULL;
	mini.last_exit = 0;
	return (mini);
}