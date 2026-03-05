# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: afournie <afournie@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/03/05 13:53:45 by afournie          #+#    #+#              #
#    Updated: 2026/03/05 13:57:49 by afournie         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

MAKEFLAGS += -s

NAME        = minishell
CC          = cc
CFLAGS      = -Wall -Werror -Wextra

LIBFT_DIR   = libft
LIBFT       = $(LIBFT_DIR)/libft.a
INC         = -I includes -I $(LIBFT_DIR)

SRCS        =  main.c \

OBJS        = $(SRCS:.c=.o)

RED			= \033[0;31m
GREEN		= \033[0;32m
CYAN		= \033[0;36m
RESET		= \033[0m

all: $(NAME)

$(NAME): $(LIBFT) $(OBJS)
	@$(CC) $(CFLAGS) $(OBJS) $(LIBFT) -o $(NAME) && echo "$(GREEN)[OK] Compilation réussie, exécutable créé$(RESET)" || (echo "$(RED)[FAIL] Compilation échouée$(RESET)"; exit 1)

$(LIBFT):
	@make -C $(LIBFT_DIR) && echo "$(GREEN)[OK] Libft créé $(RESET)" || (echo "$(RED)[FAIL] Compilation Libft échouée$(RESET)"; exit 1)"

%.o: %.c
	@$(CC) $(CFLAGS) $(INC) -c $< -o $@

clean:
	@make clean -C $(LIBFT_DIR)
	@rm -f $(OBJS)
	@echo "$(CYAN)Fichiers objets supprimés$(RESET)"

fclean: clean
	@make fclean -C $(LIBFT_DIR)
	@rm -f $(NAME)
	@echo "$(CYAN)Exécutable supprimé$(RESET)"

re: fclean all

.PHONY: all clean fclean re
