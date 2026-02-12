/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   poubelle.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttiprez <ttiprez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/02 16:45:24 by afournie          #+#    #+#             */
/*   Updated: 2026/02/12 14:42:00 by ttiprez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <dirent.h>
#include <errno.h>

// un genre de ls -a trouvee sur stackoverflow
// a voir si c'est utile
int	ls(void)
{
	DIR				*dirp;
	struct dirent	*dp;

	dirp = opendir(".");
	if (!dirp)
	{
		perror("opendir()");
		exit(1);
	}
	dp = readdir(dirp);
	while (readdir(dirp))
	{
		puts(dp->d_name);
		dp = readdir(dirp);
	}
	if (errno)
	{
		perror("readdir()");
		exit(1);
	}
	return (0);
}
