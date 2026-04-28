/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttiprez <ttiprez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/10 15:26:37 by ttiprez           #+#    #+#             */
/*   Updated: 2026/04/28 13:42:40 by ttiprez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*extract_var_name(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '?')
		return (ft_substr(str, 0, 1));
	while (str[i] && (ft_isalnum(str[i]) || str[i] == '_'))
		i++;
	return (ft_substr(str, 0, i));
}

static int	add_var(char **new_str, char *var_name, char *var_val, t_mini *mini)
{
	int		len;
	char	*tmp;

	if (!var_val)
		var_val = "";
	tmp = ft_strjoin(*new_str, var_val);
	if (!tmp)
		exit((ft_free(), cleaning(&mini->env), ENOMEM));
	*new_str = tmp;
	len = ft_strlen(var_name);
	return (len);
}

static void	expand_str(char **str, t_state *state, t_mini *mini)
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
			if (!tmp)
				exit((ft_free(), cleaning(&mini->env), ENOMEM));
			if ((*str)[i] == '?')
				i += add_var(&new, tmp, ft_itoa(mini->last_exit), mini);
			else
				i += add_var(&new, tmp, get_envp(mini->env, tmp), mini);
		}
		else
		{
			tmp = ft_strnjoin(new, &(*str)[i], 1);
			if (!tmp)
				exit((ft_free(), cleaning(&mini->env), ENOMEM));
			new = tmp;
			i++;
		}
	}
	*str = new;
}

void	expand(char **str, t_mini *mini)
{
	t_state	state;

	state = DEFAULT;
	expand_str(str, &state, mini);
}
