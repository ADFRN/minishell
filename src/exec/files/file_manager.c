/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_manager.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afournie <afournie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 19:51:44 by ttiprez           #+#    #+#             */
/*   Updated: 2026/04/08 11:22:41 by afournie         ###   ########.fr       */
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
	int	input_fd;

	if (cmd->heredoc)
		input_fd = open(cmd->redir_in, O_RDONLY);
	else if (cmd->redir_in)
	{
		input_fd = open("/tmp/.pipex_heredoc", O_WRONLY | O_CREAT | O_TRUNC, \
			0644);
		if (input_fd < 0)
			return (perror("/tmp/.pipex_heredoc"), -1);
		read_stdin(input_fd, cmd->redir_in);
		close(input_fd);
		input_fd = open("/tmp/.pipex_heredoc", O_RDONLY);
		if (input_fd < 0)
			return (perror("/tmp/.pipex_heredoc"), -1);
	}
	else
		input_fd = STDIN_FILENO;
	dup2(input_fd, STDIN_FILENO);
	return (input_fd);
}

int	open_output_file(t_cmd *cmd)
{
	int	output_fd;

	if (cmd->append)
		output_fd = open(cmd->redir_out, O_WRONLY | O_CREAT | O_APPEND, 0644);
	else if (cmd->redir_out)
		output_fd = open(cmd->redir_out, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else
		output_fd = STDOUT_FILENO;
	if (!output_fd)
		exit((ft_free(), EXIT_FAILURE));
	dup2(output_fd, STDOUT_FILENO);
	return (output_fd);
}
