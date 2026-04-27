/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_manager.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttiprez <ttiprez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/16 11:53:02 by ttiprez           #+#    #+#             */
/*   Updated: 2026/04/27 11:36:30 by ttiprez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*generate_filename(char *base)
{
	unsigned int	value;
	int				fd;
	char			*to_add;
	char			*res;

	fd = open("/dev/urandom", O_RDONLY);
	if (fd < 0)
		return (NULL);
	if (read(fd, &value, sizeof(value)) < 0)
		return (close(fd), NULL);
	close(fd);
	to_add = ft_itoa(value);
	res = ft_strjoin(base, to_add);
	free(to_add);
	return (res);
}

static char	*run_heredoc(t_redirection *redir)
{
	char	buf[100000];
	int		nb_read;
	char	*filename;
	int		fd;
	char	*other_eof;

	filename = generate_filename("/tmp/.ms_heredoc_");
	fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	other_eof = ft_strjoin(redir->filename, "\n");
	if (!other_eof)
		return (close(fd), NULL);
	if (fd < 0)
		return (NULL);
	while (1)
	{
		free((ft_putstr("> "), nb_read = read(0, buf, sizeof(buf)), NULL));
		if (nb_read <= 0)
			break ;
		buf[nb_read] = 0;
		if (!ft_strcmp(buf, redir->filename)
			|| !ft_strcmp(buf, other_eof))
			break ;
		write(fd, buf, nb_read);
	}
	return (close(fd), filename);
}

bool	preprocess_heredocs(t_cmd **lst_cmd)
{
	t_cmd			*curr_cmd;
	t_redirection	*curr_redir;

	curr_cmd = *lst_cmd;
	while (curr_cmd)
	{
		curr_redir = curr_cmd->redir;
		while (curr_redir)
		{
			if (curr_redir->redir_type == REDIR_HEREDOC)
			{
				curr_redir->filename = run_heredoc(curr_redir);
				if (!curr_redir->filename)
					return (ft_free(), false);
			}
			curr_redir = curr_redir->next;
		}
		curr_cmd = curr_cmd->next;
	}
	return (true);
}

void	delete_heredocs_files(t_cmd **lst_cmd)
{
	t_cmd			*curr_cmd;
	t_redirection	*curr_redir;

	curr_cmd = *lst_cmd;
	while (curr_cmd)
	{
		curr_redir = curr_cmd->redir;
		while (curr_redir)
		{
			if (curr_redir->redir_type == REDIR_HEREDOC)
			{
				if (unlink(curr_redir->filename) == -1)
					perror("unlink");
			}
			curr_redir = curr_redir->next;
		}
		curr_cmd = curr_cmd->next;
	}
}
