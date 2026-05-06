/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_manager2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afournie <afournie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/04 17:12:07 by afournie          #+#    #+#             */
/*   Updated: 2026/05/04 17:14:06 by afournie         ###   ########.fr       */
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
	return (res);
}

static void	heredoc_loop(t_redirection *redir, int fd)
{
	char	*line;

	while (1)
	{
		line = readline("> ");
		if (!line)
		{
			if (g_sig == SIGINT)
				break ;
			printf("Minishell: warning: here-document delimited \
by end-of-file (wanted `%s')\n", redir->filename);
			break ;
		}
		if (!ft_strcmp(line, redir->filename))
		{
			free(line);
			break ;
		}
		write(fd, line, ft_strlen(line));
		write(fd, "\n", 1);
		free(line);
	}
}

char	*run_heredoc(t_redirection *redir)
{
	char	*filename;
	int		fd;
	char	*eof;

	filename = generate_filename("/tmp/.ms_heredoc_");
	fd = open(filename, O_RDWR | O_CREAT | O_TRUNC, 0644);
	if (fd < 0)
		return (NULL);
	eof = ft_strjoin(redir->filename, "\n");
	if (!eof)
		return (NULL);
	heredoc_loop(redir, fd);
	return (filename);
}
