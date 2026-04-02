/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   garbage_collector.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttiprez <ttiprez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/31 14:35:53 by afournie          #+#    #+#             */
/*   Updated: 2026/04/02 11:17:14 by ttiprez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*new_gnode(t_garbage **list_head, int size)
{
	t_garbage	*new;
	t_garbage	*temp;
	void		*ptr;

	new = malloc(sizeof(t_garbage));
	if (!new)
		return (NULL);
	new->ptr = malloc(size);
	if (!new->ptr)
		return (free(new), NULL);
	ptr = new->ptr;
	new->next = NULL;
	if (*list_head == NULL)
		*list_head = new;
	else
	{
		temp = *list_head;
		while (temp->next)
			temp = temp->next;
		temp->next = new;
	}
	return (ptr);
}

void	*ft_malloc(int size)
{
	static t_garbage	*head = NULL;
	void				*ptr;

	if (size == -1)
		return (&head);
	ptr = new_gnode(&head, size);
	if (!ptr)
		return (ft_putstr_fd("malloc error\n", 2), NULL);
	return (ptr);
}

void	ft_free(void)
{
	t_garbage	**lst_head;
	t_garbage	*head;
	t_garbage	*tmp;

	lst_head = ft_malloc(-1);
	head = *lst_head;
	while (head != NULL)
	{
		tmp = head;
		head = head->next;
		free(tmp->ptr);
		free(tmp);
	}
	*lst_head = NULL;
}
