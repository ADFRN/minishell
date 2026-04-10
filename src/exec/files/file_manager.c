/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_manager.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttiprez <ttiprez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 19:51:44 by ttiprez           #+#    #+#             */
/*   Updated: 2026/04/10 15:33:31 by ttiprez          ###   ########.fr       */
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

int	open_input_file(t_cmd *cmd)
{
	t_redirection	*c;
	int				input_fd;

	c = cmd->redir_in;
	if (!c)
		input_fd = STDIN_FILENO;
	while (c)
	{
		if (!cmd->redir_in->heredoc_or_append && !c->next)
			input_fd = open(c->filename, O_RDONLY);
		else if (cmd->redir_in->heredoc_or_append)
		{
			input_fd = open("/tmp/.pipex_heredoc", \
				O_WRONLY | O_CREAT | O_TRUNC, 0644);
			if (input_fd < 0)
				return (perror("/tmp/.pipex_heredoc"), -1);
			read_stdin(input_fd, c->filename);
			close(input_fd);
			input_fd = open("/tmp/.pipex_heredoc", O_RDONLY);
			if (input_fd < 0)
				return (perror("/tmp/.pipex_heredoc"), -1);	
		}
		c = c->next;
	}
	return (input_fd);
}

int	open_output_file(t_cmd *cmd)
{
	int				output_fd;
	t_redirection	*c;

	c = cmd->redir_out;
	if (!c)
		output_fd = STDOUT_FILENO;
	while (c)
	{
		if (c->heredoc_or_append)
			output_fd = open(c->filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
		else if (c->filename)
			output_fd = open(c->filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		else
			output_fd = STDOUT_FILENO;
		if (output_fd < 0)
			return (perror("output_fd"), -1);
		c = c->next;
	}
	return (output_fd);
}
