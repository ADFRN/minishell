/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_manager.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttiprez <ttiprez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 19:51:44 by ttiprez           #+#    #+#             */
/*   Updated: 2026/04/13 12:58:57 by ttiprez          ###   ########.fr       */
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

int	open_input_file(t_redirection *redir) // RENVOIE PAS LE CONTENU
{
	int	fd;

	while (redir)
	{
		if (redir->heredoc_or_append)
			fd = handle_heredoc(redir);
		else
			fd = open(redir->filename, O_RDONLY);
		if (fd < 0 && !redir->heredoc_or_append)
			return (perror(redir->filename), -1);
		close(fd);
		redir = redir->next;
	}
	if (dup2(fd, STDIN_FILENO) == -1)
			return (close(fd), -1);
	return (0);
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
