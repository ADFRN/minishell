/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afournie <afournie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/27 10:28:43 by ttiprez           #+#    #+#             */
/*   Updated: 2026/04/01 12:01:41 by afournie         ###   ########.fr       */
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
	cmd->args = NULL;
	cmd->redir_in = NULL;
	cmd->redir_out = NULL;
	cmd->append = false;
	cmd->heredoc = false;
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

// void	ft_cmd_clear(t_cmd **lst)
// {
// 	t_cmd	*next;

// 	if (!lst || !*lst)
// 		return ;
// 	while (*lst)
// 	{
// 		next = (*lst)->next;
// 		free((*lst)->args);
// 		free((*lst)->redir_in);
// 		free((*lst)->redir_out);
// 		free(*lst);
// 		*lst = next;
// 	}
// }

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

char	**ft_token_to_args(t_token **start)
{
	t_token	*curr;
	int		i;
	char	**args;

	curr = *start;
	i = 0;
	while (curr && curr->type == WORD)
	{
		curr = curr->next;
		i++;
	}
	args = ft_malloc(sizeof(char *) * (i + 1));
	if (!args)
		exit((ft_free(), EXIT_FAILURE));
	curr = *start;
	i = -1;
	while (curr && curr->type == WORD)
	{
		args[++i] = ft_strdup(curr->content);
		args[i] = remove_quotes(curr->content);
		curr = curr->next;
	}
	args[i + 1] = NULL;
	*start = curr;
	return (args);
}

static void	print_split(char **str)
{
	printf("[");
	for (int i = 0; str[i]; i++)
	{
		printf("\"%s\", ", str[i]);
	}
	printf("NULL");
	printf("]\n");
}

void	ft_print_lst_cmd(t_cmd **lst_cmd)
{
	t_cmd	*current;
	int		i;

	current = *lst_cmd;
	i = 0;
	while (current)
	{
		printf("\n\t\tMaillon n%d :\n", i++);
		printf("args		= ");
		print_split(current->args);
		printf("redir_int	= %s\n", current->redir_in);
		printf("redir_out	= %s\n", current->redir_out);
		printf("heredoc		= %s\n", current->heredoc ? "true" : "false");
		printf("append		= %s\n", current->append ? "true" : "false");
		printf("next		= %s\n", current->next ? "yes" : "no");
		current = current->next;
	}
}
