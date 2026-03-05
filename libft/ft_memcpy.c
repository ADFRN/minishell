/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afournie <afournie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/05 13:55:55 by afournie          #+#    #+#             */
/*   Updated: 2025/11/11 11:15:54 by afournie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t size)
{
	size_t	i;

	if (!dest && !src)
		return (0);
	i = 0;
	while (i < size)
	{
		((char *)dest)[i] = ((char *)src)[i];
		i++;
	}
	return ((void *)dest);
}
