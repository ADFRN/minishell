/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttiprez <ttiprez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/09 15:23:51 by ttiprez           #+#    #+#             */
/*   Updated: 2026/03/24 12:51:24 by ttiprez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

/* --- LIBRARIES --- */
# include "libft.h"
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdbool.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>
# include <errno.h>
# include <linux/limits.h>

/* --- ENUMS & STRUCTS --- */
typedef enum e_state
{
	DEFAULT,
	IN_SINGLE_QUOTE,
	IN_DOUBLE_QUOTE
}	t_state;

typedef enum e_token_type
{
	WORD,
	PIPE,
	INPUT,
	OUTPUT,
	HEREDOC,
	APPEND
}	t_token_type;

typedef struct s_token
{
	char					*content;
	t_token_type			type;
	struct s_token			*next;
	struct s_token			*prev;
}	t_token;

/* --- PROTOTYPES --- */

// Lexer
char			**lexer(char *rl, int i);
//	lexer_utils.c
bool			have_valid_quotes(char *str);
bool			is_metachar(char c);
int				get_operator_len(char *str);
int				get_word_len(char *str);
void			set_state(char c, t_state *state);
//	tokenizer.c
t_token			*tokenizer(char *line);
//	token_utils.c
t_token			*ft_token_new(char *content, t_token_type type);
void			ft_token_add_back(t_token **lst, t_token *new);
void			ft_token_clear(t_token **lst);
t_token_type	get_operator_type(char *str);
void			print_tokens(t_token **lst);

// Expander
void			expand(char **token, char **envp);
char			*get_envp(char **envp, char *to_find);

// Env
char			**env_cpy(char **envp);
void			free_env(char **env);

// Exec & Builtins
void			exec_cmd(char *rl);
void			echo_cmd(char *s);
char			*pwd_cmd(void);
int				suitebordel(int ac, char **av, char **envcpy);

// Signals
void			init_signal(void);

// Utils
int				ft_pathlen(char *str);
char			*get_envp(char **envp, char *to_find);
int				get_env_i(char **envcpy, char *s);

#endif