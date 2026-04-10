/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttiprez <ttiprez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/09 14:26:17 by ttiprez           #+#    #+#             */
/*   Updated: 2026/04/10 12:23:12 by ttiprez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_realloc(void *ptr, size_t newsize)
{
	char	*newptr;
	size_t	current_size;

	if (ptr == 0)
		return (ft_malloc(newsize));
	current_size = sizeof(ptr);
	if (newsize <= current_size)
		return (ptr);
	newptr = ft_malloc(newsize);
	ft_memcpy(ptr, newptr, current_size);
	return (newptr);
}