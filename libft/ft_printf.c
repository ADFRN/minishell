/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afournie <afournie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/12 15:45:01 by afournie          #+#    #+#             */
/*   Updated: 2025/12/16 14:06:53 by afournie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_is_format(const char s)
{
	return (s == FORMAT_CHAR || s == FORMAT_DECIMAL || s == FORMAT_HEXALOW
		|| s == FORMAT_HEXAUPP || s == FORMAT_INT || s == FORMAT_PERCENT
		|| s == FORMAT_POINT || s == FORMAT_STR || s == FORMAT_UDESC);
}

void	ft_print(const char s, va_list *arg, int *count)
{
	if (s == FORMAT_CHAR)
	{
		ft_putchar_fd(va_arg(*arg, int), 1);
		(*count)++;
	}
	else if (s == FORMAT_DECIMAL || s == FORMAT_INT)
		(*count) += ft_putnbr(va_arg(*arg, int));
	else if (s == FORMAT_UDESC)
		(*count) += ft_putnbr_udesc(va_arg(*arg, unsigned int));
	else if (s == FORMAT_HEXALOW)
		(*count) += ft_putnbr_hexa_low(va_arg(*arg, unsigned int));
	else if (s == FORMAT_HEXAUPP)
		(*count) += ft_putnbr_hexa_up(va_arg(*arg, unsigned int));
	else if (s == FORMAT_PERCENT)
	{
		ft_putchar_fd('%', 1);
		(*count)++;
	}
	else if (s == FORMAT_POINT)
		(*count) += ft_print_ptr(va_arg(*arg, void *));
	else if (s == FORMAT_STR)
		(*count) += ft_putstr(va_arg(*arg, char *));
}

int	ft_printf(const char *s, ...)
{
	int		i;
	int		count;
	va_list	args;

	i = -1;
	count = 0;
	if (!s || (s[0] == '%' && !s[1]))
		return (-1);
	va_start(args, s);
	while (s[++i])
	{
		if (s[i] == '%' && ft_is_format(s[i + 1]))
		{
			ft_print(s[i + 1], &args, &count);
			i++;
		}
		else
		{
			ft_putchar_fd(s[i], 1);
			count++;
		}
	}
	va_end(args);
	return (count);
}
