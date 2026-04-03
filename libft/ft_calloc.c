/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttiprez <ttiprez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 11:02:28 by afournie          #+#    #+#             */
/*   Updated: 2026/04/03 18:18:23 by ttiprez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	size_t	total;
	void	*pnt;

	total = nmemb * size;
	pnt = malloc(total);
	if (pnt == NULL)
		return (NULL);
	ft_memset(pnt, 0, total);
	return (pnt);
}
