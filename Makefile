# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ttiprez <ttiprez@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/03/09 15:27:07 by ttiprez           #+#    #+#              #
#    Updated: 2026/04/27 20:28:10 by ttiprez          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

MAKEFLAGS += -s

# --- COLORS ---
RED		= \033[1;31m
GREEN	= \033[1;32m
YELLOW	= \033[1;33m
BLUE	= \033[1;34m
MAGENTA	= \033[1;35m
CYAN	= \033[1;36m
WHITE	= \033[1;37m
RESET	= \033[0m

# --- PIXEL ART ---
define MINISHELL_ART
$(CYAN)      _________________$(RESET)
$(CYAN)     |  $(WHITE)Minishell 1.0$(CYAN)  |$(RESET)
$(CYAN)     |  $(GREEN)>_ ready      $(CYAN) |$(RESET)
$(CYAN)     |_______(_)_______|$(RESET)
$(CYAN)   _______________________$(RESET)
$(CYAN)  /                       \\$(RESET)
$(CYAN) /_________________________\\$(RESET)
endef
export MINISHELL_ART

# --- CONFIG ---
NAME		= minishell
CC			= cc
CFLAGS		= -Wall -Wextra -Werror -g
LDFLAGS		= -lreadline

SRC_DIR		= src
OBJ_DIR		= obj
LIBFT_DIR	= libft
INC_DIR		= includes

# --- SOURCES (Liste explicite pour la norme) ---
SRCS		=	$(SRC_DIR)/builtins/cd.c					\
				$(SRC_DIR)/builtins/echo.c					\
				$(SRC_DIR)/builtins/env.c					\
				$(SRC_DIR)/builtins/exit.c					\
				$(SRC_DIR)/builtins/export.c				\
				$(SRC_DIR)/builtins/export_print.c			\
				$(SRC_DIR)/builtins/export_utils.c			\
				$(SRC_DIR)/builtins/pwd.c					\
				$(SRC_DIR)/builtins/unset.c					\
				$(SRC_DIR)/expander/expand.c				\
				$(SRC_DIR)/lexer/lexer_utils.c				\
				$(SRC_DIR)/lexer/lexer.c					\
				$(SRC_DIR)/parser/parser.c					\
				$(SRC_DIR)/parser/syntax_error.c			\
				$(SRC_DIR)/main/main.c						\
				$(SRC_DIR)/signals/signals.c				\
				$(SRC_DIR)/struct/cmd_utils.c				\
				$(SRC_DIR)/struct/redirection_utils.c		\
				$(SRC_DIR)/struct/token_utils.c				\
				$(SRC_DIR)/struct/mini_utils.c				\
				$(SRC_DIR)/struct/env_utils.c				\
				$(SRC_DIR)/struct/env_utils2.c				\
				$(SRC_DIR)/struct/env_utils3.c				\
				$(SRC_DIR)/utils/utils.c					\
				$(SRC_DIR)/utils/utils2.c					\
			  	$(SRC_DIR)/exec/utils/exec_utils.c			\
			  	$(SRC_DIR)/exec/parsing/path_parsing.c		\
			  	$(SRC_DIR)/exec/execution/builtins_exec.c	\
			  	$(SRC_DIR)/exec/execution/child_exec.c		\
			  	$(SRC_DIR)/exec/files/file_manager.c		\
			  	$(SRC_DIR)/exec/files/heredoc_manager.c		\
			  	$(SRC_DIR)/exec/pipex.c						\
			  	$(SRC_DIR)/routine/routine.c				\
				$(SRC_DIR)/DEBUG/DEBUG.c					\

OBJS		=	$(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)
LIBFT		=	$(LIBFT_DIR)/libft.a

# --- RULES ---
all: $(NAME)

$(NAME): $(LIBFT) $(OBJS)
	@printf "$(YELLOW)Linking $(NAME)...$(RESET)\n"
	@$(CC) $(CFLAGS) $(OBJS) $(LIBFT) $(LDFLAGS) -o $(NAME)
	@printf "%b\n""$$MINISHELL_ART"
	@printf "\n\n$(GREEN)Minishell est prêt à l'emploi !$(RESET)\n"

$(LIBFT):
	@printf "$(MAGENTA)Construction de la Libft...$(RESET)\n"
	@make -C $(LIBFT_DIR)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -I$(INC_DIR) -I$(LIBFT_DIR) -c $< -o $@
	@printf "$(BLUE)Compiling:$(RESET)%s\n" "$(notdir $<)"

clean:
	@printf "$(RED)Nettoyage des objets...$(RESET)\n"
	@make clean -C $(LIBFT_DIR)
	@rm -rf $(OBJ_DIR)

fclean: clean
	@printf "$(RED)Suppression de l'exécutable...$(RESET)\n"
	@make fclean -C $(LIBFT_DIR)
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
