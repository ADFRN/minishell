/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afournie <afournie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/10 15:26:37 by ttiprez           #+#    #+#             */
/*   Updated: 2026/04/10 14:55:34 by ttiprez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*extract_var_name(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '?' || ft_isdigit(str[i]))
		return (ft_substr(str, 0, 1));
	while (str[i] && (ft_isalnum(str[i]) || str[i] == '_'))
		i++;
	return (ft_substr(str, 0, i));
}

static int	add_var(char **new_str, char *var_name, char *var_val)
{
	int		len;
	char	*tmp;

	if (!var_val)
		var_val = "";
	tmp = ft_strjoin(*new_str, var_val);
	*new_str = tmp;
	len = ft_strlen(var_name);
	return (len);
}

static void	expand_str(char **str, char **envp, t_state *state)
{
	char	*new;
	char	*tmp;
	int		i;

	new = ft_strdup("");
	i = 0;
	while ((*str)[i])
	{
		set_state((*str)[i], state);
		if ((*str)[i] == '$' && (*state != IN_SINGLE_QUOTE))
		{
			i++;
			tmp = extract_var_name(&(*str)[i]);
			i += add_var(&new, tmp, get_envp(envp, tmp));
		}
		else
		{
			tmp = ft_strnjoin(new, &(*str)[i], 1);
			new = tmp;
			i++;
		}
	}
	*str = new;
}

void	expand(char **str, char **envp)
{
	t_state	state;

	state = DEFAULT;
	expand_str(str, envp, &state);
}
