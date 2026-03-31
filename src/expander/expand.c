/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttiprez <ttiprez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/10 15:26:37 by ttiprez           #+#    #+#             */
/*   Updated: 2026/03/24 14:45:04 by ttiprez          ###   ########.fr       */
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

static void	expand_token(t_token *token, char **envp, t_state *state)
{
	char	*new;
	char	*tmp;
	int		i;

	new = ft_strdup("");
	i = 0;
	while (token->content[i])
	{
		set_state(token->content[i], state);
		if (token->content[i] == '$' && (*state != IN_SINGLE_QUOTE))
		{
			i++;
			tmp = extract_var_name(&token->content[i]);
			i += add_var(&new, tmp, get_envp(envp, tmp));
		}
		else
		{
			tmp = ft_strnjoin(new, &token->content[i], 1);
			free(new);
			new = tmp;
			i++;
		}
	}
	free(token->content);
	token->content = new;
}

void	expand(t_token **lst_tokens, char **envp)
{
	int		i;
	t_state	state;
	t_token	*current;

	i = -1;
	current = *lst_tokens;
	while (current)
	{
		state = DEFAULT;
		expand_token(current, envp, &state);
		current = current->next;
	}
}
