/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttiprez <ttiprez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/27 10:28:43 by ttiprez           #+#    #+#             */
/*   Updated: 2026/04/21 16:19:17 by ttiprez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_cmd	*ft_cmd_new(void)
{
	t_cmd	*cmd;

	cmd = ft_malloc(sizeof(t_cmd));
	if (!cmd)
	{
		ft_free();
		exit(EXIT_FAILURE);
	}
	cmd->cmd_with_path = NULL;
	cmd->envp = NULL;
	cmd->args = NULL;
	cmd->redir = NULL;
	cmd->next = NULL;
	return (cmd);
}

void	ft_cmd_add_back(t_cmd **lst, t_cmd *new)
{
	t_cmd	*last;

	if (!*lst)
	{
		*lst = new;
		return ;
	}
	last = *lst;
	while (last->next)
		last = last->next;
	last->next = new;
}

static char	*remove_quotes(char *str)
{
	char	*result;
	int		i;
	int		j;
	char	quote;

	result = ft_malloc(strlen(str) + 1);
	if (!result)
		exit((ft_free(), EXIT_FAILURE));
	i = 0;
	j = 0;
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '"')
		{
			quote = str[i++];
			while (str[i] && str[i] != quote)
				result[j++] = str[i++];
			if (str[i])
				i++;
		}
		else
			result[j++] = str[i++];
	}
	result[j] = '\0';
	return (result);
}

static int	args_len(t_token *curr)
{
	int	i;

	i = 0;
	while (curr && curr->type != PIPE)
	{
		if (curr->type == WORD && (!curr->prev
				|| curr->prev->type == WORD || curr->prev->type == PIPE))
			i++;
		curr = curr->next;
	}
	return (i);
}

char	**get_cmd_args(t_token **start)
{
	t_token	*curr;
	char	**args;
	int		i;

	curr = *start;
	i = args_len(curr);
	args = ft_malloc(sizeof(char *) * (i + 1));
	if (!args)
		exit((ft_free(), EXIT_FAILURE));
	curr = *start;
	i = -1;
	while (curr && curr->type != PIPE)
	{
		if (curr->type == WORD && (!curr->prev
				|| curr->prev->type == WORD || curr->prev->type == PIPE))
		{
			args[++i] = ft_strdup(curr->content);
			args[i] = remove_quotes(curr->content);
		}
		curr = curr->next;
	}
	return ((args[i + 1] = NULL, args));
}
