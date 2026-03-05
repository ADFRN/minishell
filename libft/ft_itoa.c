/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afournie <afournie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 14:25:08 by afournie          #+#    #+#             */
/*   Updated: 2025/11/10 14:38:19 by afournie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count_size(int n)
{
	int	i;

	if (n == 0)
		return (1);
	i = 0;
	while (n != 0)
	{
		n /= 10;
		i++;
	}
	return (i);
}

char	*ft_itoa(int num)
{
	char	*dst;
	long	number;
	int		len;
	int		sign;

	number = num;
	sign = (number < 0);
	if (sign)
		number = -number;
	len = count_size(number) + sign;
	dst = malloc((len + 1) * sizeof(char));
	if (!dst)
		return (NULL);
	dst[len] = '\0';
	while (len > sign)
	{
		dst[--len] = (number % 10) + '0';
		number /= 10;
	}
	if (sign)
		dst[0] = '-';
	return (dst);
}
