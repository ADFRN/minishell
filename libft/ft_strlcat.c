/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afournie <afournie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 14:46:05 by afournie          #+#    #+#             */
/*   Updated: 2025/11/12 10:15:26 by afournie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	fill;
	size_t	dlen;
	size_t	slen;

	if (!size)
		return (ft_strlen(src));
	i = 0;
	dlen = ft_strlen(dst);
	slen = ft_strlen(src);
	fill = size - dlen - 1;
	if (dlen >= size)
		return (size + slen);
	while (src[i] && fill--)
	{
		dst[dlen + i] = src[i];
		i++;
	}
	dst[dlen + i] = '\0';
	return (dlen + slen);
}
