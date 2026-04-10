/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttiprez <ttiprez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/27 10:28:43 by ttiprez           #+#    #+#             */
/*   Updated: 2026/04/10 15:06:51 by ttiprez          ###   ########.fr       */
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

// TODO : AJOUTER les word et pas ecraser ceux deja ecrit 
//		  (exemple echo < in cat < in ---> doit ajouter cat sans ecraser echo)
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

static void	print_split(char **str)				// DEBUG
{
	printf("[");
	for (int i = 0; str[i]; i++)
	{
		printf("\"%s\", ", str[i]);
	}
	printf("NULL]\n");
}

static void	print_redir(t_redirection **lst)	// DEBUG
{
	t_redirection	*current = *lst;

	printf("\t%-15s [", "FILENAME :");
	while (current)
	{
		printf("\"%s\", ", current->filename);
		current = current->next;
	}
	printf("NULL]\n");
	current = *lst;
	printf("\t%-15s [", "HERE/APP :");
	while (current)
	{
		printf("\"%s\", ", current->heredoc_or_append ? "yes" : "no");
		current = current->next;
	}
	printf("NULL]\n");
}

void	ft_print_lst_cmd(t_cmd **lst_cmd)		// DEBUG
{
	t_cmd	*current;
	int		i;

	current = *lst_cmd;
	i = 0;
	while (current)
	{
		printf("\n\t\tMaillon n%d :\n", i++);
		printf("envp		= ");
		if (current->args) print_split(current->args);
		else printf("NULL\n");
		printf("cmd_path	= %s\n", current->cmd_with_path);
		printf("args		= ");
		if (current->args) print_split(current->args);
		else printf("NULL\n");
		printf("redir_in	= \n");
		print_redir(&current->redir_in);
		printf("redir_out	= \n");
		print_redir(&current->redir_out);
		printf("next		= %s\n", current->next ? "yes" : "no");
		current = current->next;
	}
}
