/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afournie <afournie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 10:59:51 by afournie          #+#    #+#             */
/*   Updated: 2025/12/16 14:07:11 by afournie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_putnbr(int n)
{
	int	i;

	i = 0;
	if (n == -2147483648)
		return (ft_putstr("-2147483648"));
	if (n < 0)
	{
		i += ft_putstr("-");
		n = -n;
	}
	if (n >= 10)
		i += ft_putnbr(n / 10);
	ft_putchar_fd(n % 10 + '0', 1);
	i++;
	return (i);
}

int	ft_putnbr_udesc(unsigned int n)
{
	int	i;

	i = 0;
	if (n >= 10)
		i += ft_putnbr(n / 10);
	ft_putchar_fd(n % 10 + '0', 1);
	i++;
	return (i);
}
