/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_hexa.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afournie <afournie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 10:57:29 by afournie          #+#    #+#             */
/*   Updated: 2025/12/16 14:07:03 by afournie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_putnbr_hexa_low(unsigned long n)
{
	int	count;

	count = 0;
	if (n >= 16)
		count += ft_putnbr_hexa_low(n / 16);
	ft_putchar_fd("0123456789abcdef"[n % 16], 1);
	count++;
	return (count);
}

int	ft_putnbr_hexa_up(unsigned int n)
{
	int	count;

	count = 0;
	if (n >= 16)
		count += ft_putnbr_hexa_up(n / 16);
	ft_putchar_fd("0123456789ABCDEF"[n % 16], 1);
	count++;
	return (count);
}
