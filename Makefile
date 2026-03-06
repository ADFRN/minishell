# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: afournie <afournie@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/03/05 13:53:45 by afournie          #+#    #+#              #
#    Updated: 2026/03/06 15:34:11 by afournie         ###   ########.fr        #
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
$(CYAN)     |_________________|$(RESET)
$(CYAN)     |        _        |$(RESET)
$(CYAN)     |_______(_)_______|$(RESET)
$(CYAN)   _______________________$(RESET)
$(CYAN)  /                       \\$(RESET)
$(CYAN) /_________________________\\$(RESET)
endef
export MINISHELL_ART

# --- CONFIG ---
NAME        = minishell
CC          = cc
CFLAGS      = -Wall -Wextra -Werror

LIBFT_DIR   = libft
LIBFT       = $(LIBFT_DIR)/libft.a
INC         = -I includes -I $(LIBFT_DIR)

SRCS        = main.c \
              utils.c \
              envcpy.c \
              parser.c \
              builtin-cmd.c \
              cmd_executer.c

OBJS        = $(SRCS:.c=.o)
TOTAL_FILES := $(words $(SRCS))
CURRENT_FILE = 0

# --- RULES ---

all: $(NAME)

$(NAME): $(LIBFT) $(OBJS)
	@echo "\n$(YELLOW)Linking $(NAME)...$(RESET)"
	@$(CC) $(CFLAGS) $(OBJS) $(LIBFT) -o $(NAME)
	@echo "$$MINISHELL_ART"
	@echo "$(GREEN)Minishell est prêt à l'emploi !$(RESET)"

$(LIBFT):
	@echo "$(MAGENTA)Construction de la Libft...$(RESET)"
	@make -s -C $(LIBFT_DIR)

%.o: %.c
	@$(eval CURRENT_FILE=$(shell echo $$(($(CURRENT_FILE) + 1))))
	@printf "$(BLUE)Compiling [%d/%d]$(RESET) %-20s\r" $(CURRENT_FILE) $(TOTAL_FILES) $<
	@$(CC) $(CFLAGS) $(INC) -c $< -o $@

clean:
	@make clean -s -C $(LIBFT_DIR)
	@rm -f $(OBJS)
	@echo "$(RED)Objets de Minishell nettoyés.$(RESET)"

fclean: clean
	@make fclean -s -C $(LIBFT_DIR)
	@rm -f $(NAME)
	@echo "$(RED)Exécutable $(NAME) supprimé.$(RESET)"

re: fclean all

.PHONY: all clean fclean re
