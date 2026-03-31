/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afournie <afournie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/09 15:23:51 by ttiprez           #+#    #+#             */
/*   Updated: 2026/03/27 15:09:29 by afournie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

/* --- LIBRARIES --- */
# include "libft.h"
# include <errno.h>
# include <fcntl.h>
# include <linux/limits.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

/* --- ENUMS & STRUCTS --- */
typedef enum e_state
{
	DEFAULT,
	IN_SINGLE_QUOTE,
	IN_DOUBLE_QUOTE
}		t_state;

/* --- PROTOTYPES --- */

// Lexer
char	**lexer(char *rl, int i);
bool	have_valid_quotes(char *str);
void	set_state(char c, t_state *state);

// Expander
void	expand(char **tokens, char **envp);
char	*get_envp(char **envp, char *to_find);

// Env
void	free_env(char **env);
char	**env_cpy(char **envp);
int		count_env_vars(char **envp);

// Exec & Builtins
void	exec_cmd(char *rl);
void	echo_cmd(char *s);
char	*pwd_cmd(void);
int		suitebordel(int ac, char **av, char **envcpy);

// Signals
void	init_signal(void);

// Utils
int		ft_pathlen(char *str);
char	*add_equal(char *to_find);
void	free_split(char **splitted_words);
char	*get_envp(char **envp, char *to_find);
int		get_env_i(char **envcpy, char *s);
void	print_split(char **splitted_words);
char	*create_prompt_line(void);

#endif
