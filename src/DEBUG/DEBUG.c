/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   DEBUG.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afournie <afournie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/21 16:12:15 by ttiprez           #+#    #+#             */
/*   Updated: 2026/04/28 10:09:22 by afournie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	print_split(char **str)
{
	printf("[");
	for (int i = 0; str[i]; i++)
	{
		printf("\"%s\", ", str[i]);
	}
	printf("NULL]\n");
}

static void	print_redir(t_redirection **lst)
{
	t_redirection	*current;

	current = *lst;
	printf("\t%-15s [", "FILENAME :");
	while (current)
	{
		printf("\"%s\", ", current->filename);
		current = current->next;
	}
	printf("NULL]\n");
	current = *lst;
	printf("\t%-15s [", "TYPE :");
	while (current)
	{
		if (current->redir_type == REDIR_IN)
			printf("\"redir_in\", ");
		else if (current->redir_type == REDIR_OUT)
			printf("\"redir_out\", ");
		else if (current->redir_type == REDIR_APPEND)
			printf("\"redir_append\", ");
		else if (current->redir_type == REDIR_HEREDOC)
			printf("\"redir_heredoc\", ");
		current = current->next;
	}
	printf("NULL]\n");
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
		printf("envp		= %s\n", current->envp ? "yes" : "no");
		printf("cmd_path	= %s\n", current->cmd_with_path);
		printf("args		= ");
		if (current->args)
			print_split(current->args);
		else
			printf("NULL\n");
		printf("redir		= \n");
		print_redir(&current->redir);
		printf("next		= %s\n", current->next ? "yes" : "no");
		current = current->next;
	}
}

static char	*type_to_str(t_token_type type)
{
	if (type == PIPE)
		return ("PIPE");
	else if (type == HEREDOC)
		return ("HEREDOC");
	else if (type == APPEND)
		return ("APPEND");
	else if (type == OUTPUT)
		return ("OUTPUT");
	else if (type == INPUT)
		return ("INPUT");
	return ("WORD");
}

void	print_tokens(t_token **lst)
{
	t_token	*current;

	current = *lst;
	printf("WORD | TYPE\n");
	while (current)
	{
		printf("%-60s | %s\n", current->content, type_to_str(current->type));
		current = current->next;
	}
}
