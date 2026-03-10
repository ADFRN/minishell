# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: afournie <afournie@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/03/09 15:27:07 by ttiprez           #+#    #+#              #
#    Updated: 2026/03/10 13:19:40 by afournie         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

MAKEFLAGS += -s

# --- COLORS ---
RED     = \033[1;31m
GREEN   = \033[1;32m
YELLOW  = \033[1;33m
BLUE    = \033[1;34m
MAGENTA = \033[1;35m
CYAN    = \033[1;36m
WHITE   = \033[1;37m
RESET   = \033[0m

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
NAME        = minishell
CC          = cc
CFLAGS      = 
LDFLAGS     = -lreadline

SRC_DIR     = src
OBJ_DIR     = obj
LIBFT_DIR   = libft
INC_DIR     = includes

# --- SOURCES (Liste explicite pour la norme) ---
SRCS        =	$(SRC_DIR)/builtins/builtins.c		\
				$(SRC_DIR)/env/env_utils.c			\
				$(SRC_DIR)/exec/cmd_executer.c		\
				$(SRC_DIR)/expander/expand.c		\
            	$(SRC_DIR)/lexer/lexer_utils.c		\
				$(SRC_DIR)/lexer/lexer.c			\
				$(SRC_DIR)/main/main.c				\
				$(SRC_DIR)/signals/signals.c		\
				$(SRC_DIR)/utils/utils.c			\

OBJS        = $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)
LIBFT       = $(LIBFT_DIR)/libft.a

# --- RULES ---
all: $(NAME)

$(NAME): $(LIBFT) $(OBJS)
	@echo "$(YELLOW)Linking $(NAME)...$(RESET)"
	@$(CC) $(CFLAGS) $(OBJS) $(LIBFT) $(LDFLAGS) -o $(NAME)
	@echo "$$MINISHELL_ART"
	@echo "$(GREEN)Minishell est prêt à l'emploi !$(RESET)"

$(LIBFT):
	@echo "$(MAGENTA)Construction de la Libft...$(RESET)"
	@make -C $(LIBFT_DIR)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -I$(INC_DIR) -I$(LIBFT_DIR) -c $< -o $@
	@echo "$(BLUE)Compiling:$(RESET) $(notdir $<)"

clean:
	@echo "$(RED)Nettoyage des objets...$(RESET)"
	@make clean -C $(LIBFT_DIR)
	@rm -rf $(OBJ_DIR)

fclean: clean
	@echo "$(RED)Suppression de l'exécutable...$(RESET)"
	@make fclean -C $(LIBFT_DIR)
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
