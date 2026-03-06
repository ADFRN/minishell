/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin-cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttiprez <ttiprez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/05 13:25:55 by afournie          #+#    #+#             */
/*   Updated: 2026/03/06 13:15:02 by ttiprez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <errno.h>
#include <stdbool.h>
#include <unistd.h>
#include <stdio.h>

void	echo_cmd(char *s)
{
	printf("%s", s);
}

bool	is_absolute_path(char *s)
{
	if (s[0] == '/')
		return (true);
	return (false);
}

void	cd_cmd(char *s)
{
	if (is_absolute_path(s))
		if (chdir(s) == -1)
			perror("Error :");
}

// void	pwd_cmd(void)
// {
// 	getcwd();
// }

//int	main(int ac, char **av)
//{
//	echo_cmd(av[1]);
//	return (0);
//}
