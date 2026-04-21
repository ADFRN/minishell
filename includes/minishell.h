/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttiprez <ttiprez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/09 15:23:51 by ttiprez           #+#    #+#             */
/*   Updated: 2026/04/21 16:59:45 by ttiprez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

/* --- CONSTANTS --- */
# define _POSIX_C_SOURCE	200809L	// Pour signal.h
# define HEREDOC_LIMITS		16
	/* --- RETURN_CODE --- */
# define HERE_DOC_EXCEED	2
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

typedef struct s_lstcmd
{
	char					**cmd_split;
	char					*cmd_with_path;
	char					**envp;
	struct s_lstcmd			*next;
}							t_lstcmd;

/* --- PROTOTYPES --- */

// Lexer
t_token						*lexer(char *line);
//	lexer_utils.c
bool						have_valid_quotes(char *str);
bool						is_metachar(char c);
int							get_operator_len(char *str);
int							get_word_len(char *str);
void						set_state(char c, t_state *state);

//	token_utils.c
t_token						*ft_token_new(char *content, t_token_type type);
void						ft_token_add_back(t_token **lst, t_token *new);
void						ft_token_clear(t_token **lst);
t_token_type				get_operator_type(char *str);
void						print_tokens(t_token **lst);

//	parser.c
t_cmd						*parser(t_token **token_lst, char **env);
//	syntax_error.c
bool						check_syntax(t_token *token_lst, char **env);

// Expander
void						expand(char **str, char **envp);
char						*get_envp(char **envp, char *to_find);

// Env
void						free_env(char **env);
char						**env_cpy(char **envp);
int							count_env_vars(char **envp);

// Exec & Builtins
// void				exec_cmd(char *rl);
char						*exec_pwd(void);
int							exec_cd(t_cmd *cmd);
void						exec_env(t_cmd *cmd);
void						exec_echo(t_cmd *cmd);
void						exec_export(t_cmd *cmd, char ***envcpy);
void						exec_unset(t_cmd *cmd, char ***env_ptr);

// Signals
void						init_signal(void);
void						reset_signals_child(void);
void						ignore_signals_parent(void);

// Struct
//	cmd_utils.c
t_cmd						*ft_cmd_new(void);
void						ft_cmd_add_back(t_cmd **lst, t_cmd *new);
void						ft_print_lst_cmd(t_cmd **lst_cmd);
char						**get_cmd_args(t_token **start);

// redirection_utils.c
t_redirection				*ft_redir_new(void);
void						ft_redir_add_back(t_redirection **lst,
								t_redirection *new);

// Utils
char						*get_envp(char **envp, char *to_find);
int							get_env_i(char **envcpy, char *s);
char						*add_equal(char *to_find);
void						free_split(char **splitted_words);
void						cleaning(char **envp);

int							pipex(t_cmd **lst_cmd);
void						shell_prompt(char **envcpy);
void						exec_echo(t_cmd *cmd);

/* --- PIPEX --- */
int							pipex(t_cmd **lst_cmd);

/*****************************/
/*       path_parsing.c      */
/*****************************/
char						*get_path(char **envp);
char						*get_cmd_with_path(char *cmd, char *path);

/*****************************/
/*       builtins_exec.c     */
/*****************************/
void						exec_builtins(t_cmd *cmd);

/*****************************/
/*          child_exec.c     */
/*****************************/
int							child_action(t_cmd *cmd, int input_fd,
								int pipe_fd[2]);

/*****************************/
/*       file_manager.c      */
/*****************************/
bool						open_files(t_redirection **redir);

/*****************************/
/*     heredoc_manager.c     */
/*****************************/
bool						preprocess_heredocs(t_cmd **lst_cmd);
void						delete_heredocs_files(t_cmd **lst_cmd);

/*****************************/
/*     		utils.c		     */
/*****************************/
int							wait_for_children(pid_t last_pid);
bool						is_builtins(t_cmd *cmd);
void						cmd_not_found(char *cmd);
void						safe_close(int	*fd);

#endif