/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttiprez <ttiprez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/12 13:42:48 by ttiprez           #+#    #+#             */
/*   Updated: 2026/03/09 14:52:26 by ttiprez          ###   ########.fr       */
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
int	ft_strncmp(const char *s1, const char *s2, size_t n);
int		ft_strcmp(const char *s1, const char *s2);
char	*ft_strdup(const char *src);

/*			lexer.c		*/
char	**lexer(char *rl, int i);
void	print_each_words(char *rl);

/*			expand.c		*/\
void	expand(char **tokens, char **envp);

/*			lexer_utils.c		*/
bool	have_valid_quotes(char *str);
void	free_split(char **splitted_words);
void	print_split(char **splitted_words);
void	set_state(char c, t_state *state);

/*			testctrlc.c		*/
void	ctrlc_handler(int sig, siginfo_t *info, void *context);
void	init_signal(void);
void	exec_cmd(char *rl);

/*			cmd_executer.c	*/
void	exec_cmd(char *rl);

#endif