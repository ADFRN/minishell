/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttiprez <ttiprez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/10 15:28:54 by ttiprez           #+#    #+#             */
/*   Updated: 2026/03/23 11:10:40 by ttiprez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	go_to_end_of_word(char *str, int *i, t_state *state)
{
	while (str[*i])
	{
		set_state(str[*i], state);
		if (*state == DEFAULT && (str[*i] == ' ' || is_metachar(str[*i])))
			break;
		(*i)++;
	}
}

static char	*copy_operator(char *str, int *i)
{
    char	*op;
    int		len;

    len = get_operator_len(&str[*i]);
    op = ft_substr(str, *i, len);
    *i += len;
    return (op);
}

static char	*copy_word(char *str, int *i, t_state *state)
{
	int		str_start;
	int		word_i;
	char	*word;

	str_start = *i;
	go_to_end_of_word(str, i, state);
	word = malloc(*i - str_start + 1);
	if (!word)
		return (NULL);
	word_i = 0;
	while (str_start < *i)
		word[word_i++] = str[str_start++];
	word[word_i] = 0;
	return (word);
}

static int	count_words(char *str)
{
	int		i;
	int		nb_words;
	t_state	state;

	i = 0;
	nb_words = 0;
	state = DEFAULT;
	while (str[i])
	{
		while (str[i] && str[i] == ' ')
			i++;
		if (is_metachar(str[i]))
		{
			nb_words++;
			i += get_operator_len(&str[i]);
		}
		else
		{
			nb_words++;
			go_to_end_of_word(str, &i, &state);
		}
	}
	return (nb_words);
}

char	**lexer(char *str, int i)
{
	int		current_word;
	char	**splitted_words;
	t_state	state;

	if (!str)
		return (NULL);
	splitted_words = malloc(sizeof(char *) * (count_words(str) + 1));
	if (!splitted_words)
		return (NULL);
	current_word = 0;
	state = DEFAULT;
	while (str[i])
	{
		while (str[i] && str[i] == ' ')
			i++;
		if (str[i])
		{
			state = DEFAULT;
			if (is_metachar(str[i]))
				splitted_words[current_word++] = copy_operator(str, &i);
			else
				splitted_words[current_word++] = copy_word(str, &i, &state);
			if (!splitted_words[current_word - 1])
				return (free_split(splitted_words), NULL);
		}
	}
	splitted_words[current_word] = NULL;
	return (splitted_words);
}
