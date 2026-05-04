/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afournie <afournie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/04 12:46:40 by afournie          #+#    #+#             */
/*   Updated: 2026/05/04 12:56:46 by afournie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_tilde(char **new, int *i, t_mini *mini)
{
	char	*home;
	char	*tmp;

	home = get_envp(mini->env, "HOME");
	if (!home)
		tmp = ft_strjoin(*new, "~");
	else
		tmp = ft_strjoin(*new, home);
	if (!tmp)
		exit((cleaning(&mini->env), ENOMEM));
	*new = tmp;
	(*i)++;
}
