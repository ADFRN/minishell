/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afournie <afournie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/09 15:23:51 by ttiprez           #+#    #+#             */
/*   Updated: 2026/03/31 13:51:40 by afournie         ###   ########.fr       */
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

typedef struct s_cmd
{
	char **args;        // Le tableau pour execve (ex: ["ls", "-l", NULL])
	char *redir_in;     // Nom du fichier d'entrée ou delimiteur (si < ou <<)
	char *redir_out;    // Nom du fichier de sortie (si > ou >>)
	bool heredoc;       // Heredoc (1 si <<, 0 si <)
	bool append;        // Booléen (1 si >>, 0 si >)
	struct s_cmd *next; // Commande suivante (après un pipe)
}					t_cmd;

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

// Parser
//	parser.c
t_cmd				*parser(t_token **token_lst);
//	cmd_utils.c
t_cmd				*ft_cmd_new(void);
void				ft_cmd_add_back(t_cmd **lst, t_cmd *new);
void				ft_cmd_clear(t_cmd **lst);
void				ft_print_lst_cmd(t_cmd **lst_cmd);
char				**ft_token_to_args(t_token **start);

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

// Signals
void				init_signal(void);

// Utils
char				*get_envp(char **envp, char *to_find);
int					get_env_i(char **envcpy, char *s);
char				*add_equal(char *to_find);

#endif
