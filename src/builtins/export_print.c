/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_print.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afournie <afournie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/27 12:36:24 by afournie          #+#    #+#             */
/*   Updated: 2026/04/27 12:38:43 by afournie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	env_size(t_env *env)
{
	int	i;

	i = 0;
	while (env)
	{
		i++;
		env = env->next;
	}
	return (i);
}

static t_env	**env_to_array(t_env *env)
{
	t_env	**arr;
	int		i;
	int		size;

	i = 0;
	size = env_size(env);
	arr = malloc(sizeof(t_env *) * (size + 1));
	if (!arr)
		return (NULL);
	while (env)
	{
		arr[i++] = env;
		env = env->next;
	}
	arr[i] = NULL;
	return (arr);
}

static void	sort_env(t_env **arr)
{
	int		i;
	int		j;
	t_env	*tmp;

	i = 0;
	while (arr[i])
	{
		j = i + 1;
		while (arr[j])
		{
			if (ft_strcmp(arr[i]->key, arr[j]->key) > 0)
			{
				tmp = arr[i];
				arr[i] = arr[j];
				arr[j] = tmp;
			}
			j++;
		}
		i++;
	}
}

void	print_export(t_env *env)
{
	t_env	**arr;
	int		i;

	i = 0;
	arr = env_to_array(env);
	if (!arr)
		return ;
	sort_env(arr);
	while (arr[i])
	{
		if (arr[i]->value)
			printf("export %s=\"%s\"\n", arr[i]->key, arr[i]->value);
		else
			printf("export %s\n", arr[i]->key);
		i++;
	}
	free(arr);
}
