/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_manager.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttiprez <ttiprez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 19:51:44 by ttiprez           #+#    #+#             */
/*   Updated: 2026/04/13 14:05:03 by ttiprez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	read_stdin(int fd, char *eof)
{
	char	buf[100000];
	int		nb_read;
	char	*other_eof;

	other_eof = ft_strjoin(eof, "\n");
	if (!other_eof)
		exit((close(fd), ft_free(), EXIT_FAILURE));
	while (1)
	{
		ft_putstr_fd("> ", STDIN_FILENO);
		nb_read = read(0, buf, sizeof(buf) - 1);
		if (nb_read <= 0)
			break ;
		buf[nb_read] = 0;
		if (ft_strcmp(buf, eof) == 0 || ft_strcmp(buf, other_eof) == 0)
			break ;
		write(fd, buf, nb_read);
	}
}

static int	handle_heredoc(t_redirection *redir)
{
	int	fd;

	fd = open("/tmp/.pipex_heredoc", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd < 0)
		return (perror("/tmp/.pipex_heredoc"), -1);
	read_stdin(fd, redir->filename);
	close(fd);
	fd = open("/tmp/.pipex_heredoc", O_RDONLY);
	if (fd < 0)
		return (perror("/tmp/.pipex_heredoc"), -1);
	return (fd);
}

int	open_input_file(t_redirection *redir)
{
	int	input_fd;

	if (!redir)
		input_fd = STDIN_FILENO;
	while (redir)
	{
		if (!redir->heredoc_or_append && !redir->next)
			input_fd = open(redir->filename, O_RDONLY);
		else if (redir->heredoc_or_append)
			input_fd = handle_heredoc(redir);
		redir = redir->next;
	}
	dup2(input_fd, STDIN_FILENO);
	return (input_fd);
}

int	open_output_file(t_redirection *redir)
{
	int	fd;

	while (redir)
	{
		if (redir->heredoc_or_append)
			fd = open(redir->filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
		else
			fd = open(redir->filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (fd < 0)
			return (perror(redir->filename), -1);
		if (dup2(fd, STDOUT_FILENO) == -1)
			return (close(fd), -1);
		close(fd);
		redir = redir->next;
	}
	return (0);
}
