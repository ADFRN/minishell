/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttiprez <ttiprez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/12 13:42:48 by ttiprez           #+#    #+#             */
/*   Updated: 2026/03/06 14:08:01 by ttiprez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEADER_H
# define HEADER_H

# include <signal.h>
# include <stdbool.h>

typedef enum	e_state
{
	DEFAULT,
	IN_SINGLE_QUOTE,
	IN_DOUBLE_QUOTE
} t_state;

/*			utils.c			*/
char	*get_path(char **envp);
int		ft_strcmp(const char *s1, const char *s2);
char	*ft_strdup(const char *src);

/*			lexer.c		*/
bool	check_quotes(char *str);
int		count_words(char *str);
char	**lexer(char *rl);
void	print_each_words(char *rl);

/*			testctrlc.c		*/
void	ctrlc_handler(int sig, siginfo_t *info, void *context);
void	init_signal(void);
void	exec_cmd(char *rl);

/*			cmd_executer.c	*/
void	exec_cmd(char *rl);

#endif