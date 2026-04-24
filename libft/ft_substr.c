/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttiprez <ttiprez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 13:39:23 by afournie          #+#    #+#             */
/*   Updated: 2026/04/24 17:47:48 by ttiprez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr_classic(const char *s, unsigned int start, size_t len)
{
	char	*s1;
	size_t	s_len;
	size_t	to_copy;

	if (!s)
		return (0);
	s_len = ft_strlen(s);
	if ((size_t)start >= s_len)
	{
		s1 = ft_calloc_classic(1, sizeof(char));
		return (s1);
	}
	to_copy = s_len - (size_t)start;
	if (len < to_copy)
		to_copy = len;
	s1 = ft_calloc_classic(to_copy + 1, sizeof(char));
	if (!s1)
		return (0);
	ft_strlcpy(s1, &((char *)s)[start], to_copy + 1);
	return (s1);
}

char	*ft_substr(const char *s, unsigned int start, size_t len)
{
	char	*s1;
	size_t	s_len;
	size_t	to_copy;

	if (!s)
		return (0);
	s_len = ft_strlen(s);
	if ((size_t)start >= s_len)
	{
		s1 = ft_calloc(1, sizeof(char));
		return (s1);
	}
	to_copy = s_len - (size_t)start;
	if (len < to_copy)
		to_copy = len;
	s1 = ft_calloc(to_copy + 1, sizeof(char));
	if (!s1)
		return (0);
	ft_strlcpy(s1, &((char *)s)[start], to_copy + 1);
	return (s1);
}
