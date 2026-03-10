/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttiprez <ttiprez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/10 15:26:37 by ttiprez           #+#    #+#             */
/*   Updated: 2026/03/10 15:31:45 by ttiprez          ###   ########.fr       */
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
	free(*new_str);
	*new_str = tmp;
	len = ft_strlen(var_name);
	free(var_name);
	return (len);
}

static void	just_for_norm(char **token, char *new)
{
	free(*token);
	*token = new;
}

static void	expand_token(char **token, char **envp, t_state *state)
{
	char	*new;
	char	*name;
	char	*tmp;
	int		i;

	new = ft_calloc(1, 1);
	i = -1;
	while ((*token)[++i])
	{
		set_state((*token)[i], state);
		if ((*token)[i] == '$' && (*state != IN_SINGLE_QUOTE))
		{
			name = extract_var_name(&(*token)[i + 1]);
			if (name && name[0] != '\0')
			{
				i += add_var(&new, name, get_envp(envp, name));
				continue ;
			}
			free(name);
		}
		tmp = ft_strnjoin(new, &(*token)[i], 1);
		free(new);
		new = tmp;
	}
	just_for_norm(token, new);
}

void	expand(char **tokens, char **envp)
{
	int		i;
	t_state	state;

	i = -1;
	while (tokens[++i])
	{
		state = DEFAULT;
		expand_token(&tokens[i], envp, &state);
	}
}
