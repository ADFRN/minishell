/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afournie <afournie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/09 15:21:32 by ttiprez           #+#    #+#             */
/*   Updated: 2026/04/30 15:21:57 by afournie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_redirection	*ft_redir_new(void)
{
	t_redirection	*redir;

	redir = ft_malloc(sizeof(t_redirection));
	if (!redir)
	{
		ft_free();
		exit(EXIT_FAILURE);
	}
	redir->heredoc_fd = -1;
	redir->filename = NULL;
	redir->redir_type = -1;
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
