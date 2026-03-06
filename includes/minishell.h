/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afournie <afournie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/06 14:51:05 by afournie          #+#    #+#             */
/*   Updated: 2026/03/06 17:20:40 by afournie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include <errno.h>
# include <linux/limits.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>

// void	ctrlc_handler(int sig, siginfo_t *info, void *context);
// void	init_signal(void);

/*			utils.c			*/
char	*ft_strdup(const char *src);
int		ft_strcmp(const char *s1, const char *s2);

/*			parser.c		*/
int		count_words(char *str);
char	**split_words(char *rl);
void	print_each_words(char *rl);

/*			testctrlc.c		*/
void	exec_cmd(char *rl);

/*			cmd_executer.c	*/
void	exec_cmd(char *rl);

char	*pwd_cmd(void);
void	cd_cmd(char *s);
void	echo_cmd(char *s);
void	free_env(char **env);
char	**env_cpy(char **envp);
bool	is_absolute_path(char *s);
int		count_env_vars(char **envp);
char	*get_env(char *s, char **envp);

#endif
