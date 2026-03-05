/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afournie <afournie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 14:06:59 by afournie          #+#    #+#             */
/*   Updated: 2025/11/10 17:03:13 by afournie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	is_set(char c, const char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (c == s[i])
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strtrim(const char *s1, const char *set)
{
	int		i;
	int		j;
	int		s1_len;
	int		s2_len;
	char	*s2;

	if (!s1)
		return (NULL);
	s1_len = ft_strlen(s1);
	i = 0;
	j = s1_len;
	while (is_set(s1[i], set))
		i++;
	while (is_set(s1[--j], (char *)set))
		if (j == 0)
			break ;
	s2_len = (s1_len - i) - (s1_len - j) + 2;
	if (s2_len < 1)
		s2_len = 1;
	s2 = ft_calloc(s2_len, sizeof(char));
	if (!s2)
		return (0);
	ft_strlcpy(s2, (char *)&s1[i], s2_len);
	return (s2);
}
