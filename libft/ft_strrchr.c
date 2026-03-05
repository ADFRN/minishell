/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afournie <afournie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/05 17:33:22 by afournie          #+#    #+#             */
/*   Updated: 2025/11/10 16:53:30 by afournie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int	i;

	i = ft_strlen(s);
	while (s[i] != (unsigned char)c)
	{
		if (i == 0 && s[i] != c)
			return ((char *)0);
		i--;
	}
	return ((char *)&s[i]);
}
