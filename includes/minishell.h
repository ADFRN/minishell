/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttiprez <ttiprez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/09 15:23:51 by ttiprez           #+#    #+#             */
/*   Updated: 2026/04/10 12:43:31 by ttiprez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# define _POSIX_C_SOURCE 200809L
# define HEREDOC_LIMITS 16

/* --- RETURN_CODE --- */
# define HERE_DOC_EXCEED 2

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
# include <sys/types.h>
# include <sys/types.h>
# include <sys/wait.h>

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

typedef struct s_redirection
{
	char					*filename;			// Nom du fichier ou du EOF
	bool					heredoc_or_append;	// 1 si << ou >>
	struct s_redirection	*next;
}	t_redirection;

typedef struct s_token
{
	char			*content;
	t_token_type	type;
	struct s_token	*next;
	struct s_token	*prev;
}					t_token;

typedef struct s_cmd
{
	char			**args;        // Le tableau pour execve (ex: ["ls", "-l", NULL])
	t_redirection	*redir_in;     // Nom du fichier d'entrée ou delimiteur (si < ou <<)
	t_redirection	*redir_out;    // Nom du fichier de sortie (si > ou >>)
	struct s_cmd	*next; // Commande suivante (après un pipe)
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
t_cmd				*parser(t_token **token_lst, char **env);
//	syntax_error.c
bool				check_syntax(t_token *token_lst, char **env);

// Expander
void				expand(char **str, char **envp);
char				*get_envp(char **envp, char *to_find);

// Env
void				free_env(char **env);
char				**env_cpy(char **envp);
int					count_env_vars(char **envp);

// Exec & Builtins
// void				exec_cmd(char *rl);
void				echo_cmd(char *s);
char				*pwd_cmd(void);

// Signals
void				init_signal(void);

// Struct
//	cmd_utils.c
t_cmd				*ft_cmd_new(void);
void				ft_cmd_add_back(t_cmd **lst, t_cmd *new);
void				ft_print_lst_cmd(t_cmd **lst_cmd);
char				**ft_token_to_args(t_token **start);
// redirection_utils.c
t_redirection		*ft_redir_new(char *filename, bool heredoc_or_append);
void				ft_redir_add_back(t_redirection **lst, t_redirection *new);
t_redirection		*ft_redir_get_last(t_redirection **lst);

// Utils
char				*get_envp(char **envp, char *to_find);
int					get_env_i(char **envcpy, char *s);
char				*add_equal(char *to_find);

/* --- PIPEX --- */
int 				pipex(t_cmd **lst_cmd, char **envp);

/************************************************************/
/* Definition des constantes et codes de retour          */
/************************************************************/
# define CMD_NOT_FOUND 127
# define CMD_EXEC_ERROR 126

/************************************************************/
/* Definition de la structure des commandes               */
/************************************************************/
typedef struct s_lstcmd
{
	char				**cmd_split;
	char				*cmd_with_path;
	char				**envp;
	struct s_lstcmd		*next;
}	t_lstcmd;

/*****************************/
/*		 args_check.c		 */
/*****************************/
bool		is_heredoc(char **av);
void		argv_checker(int ac, char **av);

/*****************************/
/*		 path_parsing.c		 */
/*****************************/
char		*get_path(char **envp);
char		*get_cmd_with_path(char *cmd, char *path);

/*****************************/
/*		 split_quotes.c		 */
/*****************************/
char		**ft_split_quotes(char *s);

/*****************************/
/*		 split_utils.c		 */
/*****************************/
int			is_quote(char c);
char		*skip_spaces(char *s);
char		*skip_quote(char *s, char quote);
int			count_words(char *s);
int			word_len(char *s);

/*****************************/
/*		 pipe_exec.c		 */
/*****************************/
int			wait_for_children(pid_t last_pid);
//int			execute_pipeline(t_lstcmd *lst, int fd_in, int fd_out);

/*****************************/
/*		 child_exec.c		 */
/*****************************/
void	cmd_not_found(char *cmd);
void	close_all_fd(void);
//int			child_action(t_lstcmd *lst, t_lstcmd *cmd, int from, int to);

/*****************************/
/*		 file_manager.c		 */
/*****************************/
int			open_input_file(t_cmd *cmd);
int			open_output_file(t_cmd *cmd);

/*****************************/
/*		  cmd_list.c		 */
/*****************************/
t_lstcmd	*new_lstcmd(char **envp);
t_lstcmd	*add_lstcmd(t_lstcmd **start, t_lstcmd *to_add);
void		free_lstcmd(t_lstcmd *lst);
t_lstcmd	*init_lstcmd(bool is_hd, int ac, char **av, char **envp);

/*****************************/
/*		   cleanup.c		 */
/*****************************/
void		free_split(char **splitted_words);
void		cleanup(t_lstcmd *lst, int fd_in, int fd_out);

#endif
