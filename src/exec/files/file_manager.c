/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_manager.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttiprez <ttiprez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 19:51:44 by ttiprez           #+#    #+#             */
/*   Updated: 2026/04/17 13:44:17 by ttiprez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	open_input_file(t_redirection *redir)
{
	int	fd;

	fd = open(redir->filename, O_RDONLY);
	if (fd < 0)
		return (perror(redir->filename), -1);
	dup2(fd, STDIN_FILENO);
	close(fd);
	return (fd);
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
	dup2(fd, STDOUT_FILENO);
	close(fd);
	return (fd);
}

bool	open_files(t_redirection **redir)
{
	t_redirection	*curr_redir;

	curr_redir = *redir;
	while (curr_redir)
	{
		if (curr_redir->redir_type == REDIR_IN || \
			curr_redir->redir_type == REDIR_HEREDOC)
		{
			if (open_input_file(curr_redir) == -1)
				return (false);			
		}
		else if (curr_redir->redir_type == REDIR_OUT || \
				curr_redir->redir_type == REDIR_APPEND)
			if (open_output_file(curr_redir) == -1)
				return (false);
		curr_redir = curr_redir->next;
	}
	return (true);
}
void	prepare_fds(t_cmd *cmd, int *output_fd, int pipe_fd[2])
{
	if (cmd->next)
	{
		if (pipe(pipe_fd) == -1)
			exit((perror("pipe"), \
				close_all_fd(), free_env(cmd->envp), ft_free(), EXIT_FAILURE));
		*output_fd = pipe_fd[1];
	}
	else
		*output_fd = STDOUT_FILENO;
}
