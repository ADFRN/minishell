/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttiprez <ttiprez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/10 15:28:54 by ttiprez           #+#    #+#             */
/*   Updated: 2026/04/03 18:54:32 by ttiprez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	handle_operator(char *line, int *i, t_token **token_lst)
{
	int				content_len;
	char			*content;
	t_token_type	content_type;
	t_token			*new;

	content_len = get_operator_len(&line[*i]);
	content_type = get_operator_type(&line[*i]);
	content = ft_substr(line, *i, content_len);
	if (!content)
		return (false);
	new = ft_token_new(content, content_type);
	if (!new)
		return (free(content), false);
	ft_token_add_back(token_lst, new);
	*i += content_len;
	return (true);
}

static bool	handle_word(char *line, int *i, t_token **token_lst)
{
	int		content_len;
	char	*content;
	t_token	*new;

	content_len = get_word_len(&line[*i]);
	content = ft_substr(line, *i, content_len);
	if (!content)
		return (false);
	new = ft_token_new(content, WORD);
	if (!new)
		return (free(content), false);
	ft_token_add_back(token_lst, new);
	*i += content_len;
	return (true);
}

t_token	*tokenizer(char *line)
{
	t_token	*token_lst;
	int		i;
	bool	res;

	i = 0;
	token_lst = NULL;
	while (line[i])
	{
		while (line[i] == ' ')
			i++;
		if (!line[i])
			break ;
		if (is_metachar(line[i]))
			res = handle_operator(line, &i, &token_lst);
		else
			res = handle_word(line, &i, &token_lst);
		if (!res)
			return (ft_free(), NULL);
	}
	return (token_lst);
}
