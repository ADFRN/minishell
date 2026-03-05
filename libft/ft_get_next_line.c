/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afournie <afournie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/17 13:48:17 by afournie          #+#    #+#             */
/*   Updated: 2025/12/16 14:02:09 by afournie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*append_buf(char *stash, char *buffer)
{
	char	*tmp;

	if (!stash)
		stash = ft_strdup("");
	tmp = stash;
	stash = ft_strjoin(tmp, buffer);
	free(tmp);
	return (stash);
}

static char	*read_doc(int fd, char *buffer, char *stash)
{
	int	read_line;

	read_line = 1;
	while (!(stash && ft_strchr(stash, '\n')) && read_line > 0)
	{
		read_line = read(fd, buffer, BUFFER_SIZE);
		if (read_line == -1)
		{
			free(stash);
			return (NULL);
		}
		if (read_line == 0)
			break ;
		buffer[read_line] = '\0';
		stash = append_buf(stash, buffer);
		if (ft_strchr(buffer, '\n'))
			break ;
	}
	return (stash);
}

char	*set_line(char *line_buffer)
{
	size_t	count;
	size_t	total_len;
	char	*stash;

	count = 0;
	while (line_buffer[count] != '\n' && line_buffer[count] != '\0')
		count++;
	if (line_buffer[count] == '\0')
		return (NULL);
	total_len = ft_strlen(line_buffer);
	stash = ft_substr(line_buffer, count + 1, total_len - (count + 1));
	if (stash && stash[0] == 0)
	{
		free(stash);
		stash = NULL;
	}
	line_buffer[count + 1] = '\0';
	return (stash);
}

char	*get_next_line(int fd)
{
	static char	*stash;
	char		*line;
	char		*buffer;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buffer = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buffer)
		return (NULL);
	stash = read_doc(fd, buffer, stash);
	free(buffer);
	buffer = NULL;
	if (!stash)
		return (NULL);
	line = stash;
	stash = set_line(line);
	return (line);
}
