/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_manager.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttiprez <ttiprez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/16 11:53:02 by ttiprez           #+#    #+#             */
/*   Updated: 2026/04/17 12:15:16 by ttiprez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char *generate_filename(char *base)
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
	char	*line;
	char	*filename;
	int		fd;

	filename = generate_filename("/tmp/.ms_heredoc_");
	fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd < 0)
		return (NULL);
	while (1)
	{
		line = readline("> ");
		if (!line || g_sig == SIGINT || ft_strcmp(line, redir->filename) == 0)
		{
			free(line);
			break ;
		}
		free((ft_putendl_fd(line, fd), free(line), NULL));
	}
	close(fd);
	if (g_sig == SIGINT)
		return (NULL);		
	return (filename);
}

bool    preprocess_heredocs(t_cmd **lst_cmd)
{
    t_cmd           *curr_cmd;
    t_redirection   *curr_redir;

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
					return (false);
            }
            curr_redir = curr_redir->next;
        }
        curr_cmd = curr_cmd->next;
    }
    return (true);
}

void	delete_heredocs_files(t_cmd **lst_cmd)
{
	t_cmd           *curr_cmd;
    t_redirection   *curr_redir;

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
