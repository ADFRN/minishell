/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afournie <afournie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/09 15:23:51 by ttiprez           #+#    #+#             */
/*   Updated: 2026/04/30 15:21:48 by afournie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

/* --- CONSTANTS --- */
# define _POSIX_C_SOURCE	200809L	// Pour signal.h
# define DEFAULT_PATH		"/usr/local/bin:/usr/local/sbin:\
/usr/bin:/usr/sbin:/bin:/sbin"
# define HEREDOC_LIMITS		16
# define FD_LIMITS			1024
	/* --- RETURN_CODE --- */
# define HERE_DOC_EXCEED	2
# define EXIT_SIGNAL_BASE	128
# define CMD_NOT_FOUND		127
# define CMD_EXEC_ERROR		126
	/* --- BUILTINS --- */
# define CD					"cd"
# define ECHO				"echo"
# define PWD				"pwd"
# define ENV				"env"
# define EXPORT				"export"
# define UNSET				"unset"
# define EXIT				"exit"

/* --- LIBRARIES --- */
# include "libft.h"
# include <errno.h>
# include <fcntl.h>
# include <stdio.h>
# include <linux/limits.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdbool.h>
# include <stdlib.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>

extern volatile sig_atomic_t	g_sig;

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

typedef enum e_redir_type
{
	REDIR_IN,
	REDIR_OUT,
	REDIR_APPEND,
	REDIR_HEREDOC
}	t_redir_type;

typedef struct s_redirection
{
	int						heredoc_fd;
	char					*filename;
	t_redir_type			redir_type;
	struct s_redirection	*next;
}	t_redirection;

typedef struct s_token
{
	char					*content;
	t_token_type			type;
	struct s_token			*next;
	struct s_token			*prev;
}	t_token;

typedef struct s_cmd
{
	char					**envp;
	char					*cmd_with_path;
	char					**args;
	t_redirection			*redir;
	struct s_cmd			*next;
}	t_cmd;

typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
	struct s_env	*prev;
}	t_env;

typedef struct s_mini
{
	t_env	*env;
	t_cmd	*cmds;
	int		last_exit;
}	t_mini;

typedef struct s_lstcmd
{
	char					**cmd_split;
	char					*cmd_with_path;
	char					**envp;
	struct s_lstcmd			*next;
}							t_lstcmd;

/* --- PROTOTYPES --- */

// Lexer
t_token			*lexer(char *line);
//	lexer_utils.c
bool			have_valid_quotes(char *str);
bool			is_metachar(char c);
int				get_operator_len(char *str);
int				get_word_len(char *str);
void			set_state(char c, t_state *state);

//	parser.c
t_cmd			*parser(t_token **token_lst, t_env **env);
//	syntax_error.c
bool			check_syntax(t_token *token_lst, t_env **env);

// Expander
void			expand(char **str, t_mini *mini);

// Exec & Builtins
char			*exec_pwd(void);
int				exec_cd(t_cmd *cmd, t_env **env);
int				exec_export(t_cmd *cmd, t_env **env);
void			print_export(t_env *env);
bool			create_var(t_env **env, char *key, char *value);
int				is_valid_args(char *s);
bool			parse_kv(char *s, char **key, char **value, char **sep);
bool			update_var(t_env *env, char *key, char *value, char *sep);
int				exec_unset(t_cmd *cmd, t_env **env);
int				exec_builtins(t_mini *mini, t_cmd *cmd);
int				exec_cd(t_cmd *cmd, t_env **env);
int				exec_echo(t_cmd *cmd);
int				exec_env(t_env *env);
int				exec_exit(t_cmd *cmd, t_env **env);
int				exec_export(t_cmd *cmd, t_env **env);
int				exec_unset(t_cmd *cmd, t_env **env);

// Signals
void			ctrlc_heredoc_handler(int sig);
void			init_signal(void);
void			reset_signals_child(void);
void			ignore_signals_parent(void);

// Struct
//	cmd_utils.c
t_cmd			*ft_cmd_new(void);
void			ft_cmd_add_back(t_cmd **lst, t_cmd *new);
void			ft_print_lst_cmd(t_cmd **lst_cmd);
char			**get_cmd_args(t_token **start);

//	env_utils.c
t_env			*ft_env_new(void);
void			ft_env_add_back(t_env **lst, t_env *new);
void			ft_env_remove(t_env **lst, char *key);
void			ft_env_free(t_env **lst);
t_env			*ft_env_get(t_env **env, char *key);
t_env			*init_env(char **envp);
char			**env_to_char_tab(t_env *env);
char			*ft_env_get_val(t_env *env, char *key);
void			ft_env_update(t_env **env, char *key, char *value);

//	mini_utils.c
t_mini			ft_mini_new(void);

//	redirection_utils.c
t_redirection	*ft_redir_new(void);
void			ft_redir_add_back(t_redirection **lst,
					t_redirection *new);

//	token_utils.c
t_token			*ft_token_new(char *content, t_token_type type);
void			ft_token_add_back(t_token **lst, t_token *new);
void			ft_token_clear(t_token **lst);
t_token_type	get_operator_type(char *str);
void			print_tokens(t_token **lst);

// Utils
char			*get_envp(t_env *env, char *key);
char			*add_equal(char *to_find);
void			free_split(char **splitted_words);
void			cleaning(t_env **env);

int				pipex(t_mini *mini);
void			shell_prompt(t_mini *mini);

/*****************************/
/*       path_parsing.c      */
/*****************************/
char			*get_cmd_with_path(char *cmd, char *path);

/*****************************/
/*          child_exec.c     */
/*****************************/
int				child_action(t_mini *mini, t_cmd *cmd, int fd_in,
					int pipe_fd[2]);

/*****************************/
/*       file_manager.c      */
/*****************************/
bool			open_files(t_redirection **redir);

/*****************************/
/*     heredoc_manager.c     */
/*****************************/
bool			preprocess_heredocs(t_cmd **lst_cmd, t_mini *mini);
void			delete_heredocs_files(t_cmd **lst_cmd);

/*****************************/
/*     		utils.c		     */
/*****************************/
int				wait_for_children(pid_t last_pid);
bool			is_builtins(t_cmd *cmd);
void			cmd_not_found(char *cmd);
void			close_all_fd(void);

#endif
