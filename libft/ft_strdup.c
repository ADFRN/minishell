/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttiprez <ttiprez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 11:13:25 by afournie          #+#    #+#             */
/*   Updated: 2026/04/29 16:56:52 by ttiprez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup_classic(const char *s)
{
	int		i;
	int		size;
	char	*new;

	if (!s)
		return (NULL);
	i = 0;
	size = ft_strlen(s);
	new = malloc(sizeof(char) * (size + 1));
	if (!new)
		return (NULL);
	while (s[i])
	{
		new[i] = s[i];
		i++;
	}
	new[i] = '\0';
	return (new);
}

char	*ft_strdup(const char *s)
{
	int		i;
	int		size;
	char	*new;

	i = 0;
	if (!s)
		return (NULL);
	size = ft_strlen(s);
	new = ft_malloc(sizeof(char) * (size + 1));
	if (!new)
		return (NULL);
	while (s[i])
	{
		new[i] = s[i];
		i++;
	}
	new[i] = '\0';
	return (new);
}
