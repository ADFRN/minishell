/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_manager.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttiprez <ttiprez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 19:51:44 by ttiprez           #+#    #+#             */
/*   Updated: 2026/04/28 16:07:43 by ttiprez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	open_input_file(t_redirection *redir)
{
	int	fd;

	fd = open(redir->filename, O_RDONLY);
	if (fd < 0)
		return (perror(redir->filename), -1);
	if (dup2(fd, STDIN_FILENO) == -1)
		return (/*safe_close(&fd),*/ -1);
	//safe_close(&fd);
	return (0);
}

static int	open_output_file(t_redirection *redir)
{
	int	fd;

	if (redir->redir_type == REDIR_OUT)
		fd = open(redir->filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else
		fd = open(redir->filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd < 0)
		return (perror(redir->filename), -1);
	if (dup2(fd, STDOUT_FILENO) == -1)
		return (/*safe_close(&fd),*/ -1);
	//safe_close(&fd);
	return (0);
}

bool	open_files(t_redirection **redir)
{
	t_redirection	*curr_redir;

	curr_redir = *redir;
	while (curr_redir)
	{
		if (curr_redir->redir_type == REDIR_IN
			|| curr_redir->redir_type == REDIR_HEREDOC)
		{
			if (open_input_file(curr_redir) == -1)
				return (false);
		}
		else if (curr_redir->redir_type == REDIR_OUT
			|| curr_redir->redir_type == REDIR_APPEND)
			if (open_output_file(curr_redir) == -1)
				return (false);
		curr_redir = curr_redir->next;
	}
	return (true);
}
