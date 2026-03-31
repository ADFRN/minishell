/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afournie <afournie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/09 15:23:51 by ttiprez           #+#    #+#             */
/*   Updated: 2026/03/31 13:33:34 by afournie         ###   ########.fr       */
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
}					t_state;

typedef enum e_token_type
{
	WORD,
	PIPE,
	INPUT,
	OUTPUT,
	HEREDOC,
	APPEND
}					t_token_type;

typedef struct s_token
{
	char			*content;
	t_token_type	type;
	struct s_token	*next;
	struct s_token	*prev;
}					t_token;

/* --- PROTOTYPES --- */

// Lexer
t_token				*tokenizer(char *line);
//	lexer_utils.c
bool				have_valid_quotes(char *str);
bool				is_metachar(char c);
int					get_operator_len(char *str);
int					get_word_len(char *str);
void				set_state(char c, t_state *state);
//	token_utils.c
t_token				*ft_token_new(char *content, t_token_type type);
void				ft_token_add_back(t_token **lst, t_token *new);
void				ft_token_clear(t_token **lst);
t_token_type		get_operator_type(char *str);
void				print_tokens(t_token **lst);

// Expander
void				expand(t_token **lst_tokens, char **envp);
char				*get_envp(char **envp, char *to_find);

// Env
void				free_env(char **env);
char				**env_cpy(char **envp);
int					count_env_vars(char **envp);

// Exec & Builtins
void				exec_cmd(char *rl);
void				echo_cmd(char *s);
char				*pwd_cmd(void);
int					suitebordel(int ac, char **av, char **envcpy);

// Signals
void				init_signal(void);

// Utils
char				*get_envp(char **envp, char *to_find);
int					get_env_i(char **envcpy, char *s);

#endif
