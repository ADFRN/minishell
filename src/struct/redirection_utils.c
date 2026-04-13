/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttiprez <ttiprez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/09 15:21:32 by ttiprez           #+#    #+#             */
/*   Updated: 2026/04/10 11:53:14 by ttiprez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_redirection	*ft_redir_new(char *filename, bool heredoc_or_append)
{
	t_redirection	*redir;

	redir = ft_malloc((sizeof(t_redirection)));
	if (!redir)
	{
		ft_free();
		exit(EXIT_FAILURE);
	}
	redir->filename = filename;
	redir->heredoc_or_append = heredoc_or_append;
	redir->next = NULL;
	return (redir);
}

void	ft_redir_add_back(t_redirection **lst, t_redirection *new)
{
	t_redirection	*last;

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

t_redirection	*ft_redir_get_last(t_redirection **lst)
{
	t_redirection	*current;

	current = *lst;
	while (current->next)
		current = current->next;
	return (current);
}