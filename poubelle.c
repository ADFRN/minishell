/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   poubelle.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afournie <afournie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/02 16:45:24 by afournie          #+#    #+#             */
/*   Updated: 2026/02/02 16:46:34 by afournie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <dirent.h>
#include <errno.h>

// un genre de ls -a trouvee sur stackoverflow
// a voir si c'est utile
int	ls()
{
	DIR				*dirp;
	struct dirent	*dp;

	dirp = opendir(".");
	if (!dirp)
	{
		perror("opendir()");
		exit(1);
	}
	while ((dp = readdir(dirp)))
	{
		puts(dp->d_name);
	}
	if (errno)
	{
		perror("readdir()");
		exit(1);
	}
	return (0);
}
