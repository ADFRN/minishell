/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afournie <afournie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/11 09:53:00 by afournie          #+#    #+#             */
/*   Updated: 2025/11/11 10:38:14 by afournie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_lstsize(t_list *lst)
{
	t_list	*tmp;
	int		i;

	i = 0;
	if (!lst)
		return (0);
	tmp = lst;
	while (tmp != NULL)
	{
		i++;
		tmp = tmp->next;
	}
	return (i);
}
