# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ttiprez <ttiprez@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/11/20 17:58:06 by ttiprez           #+#    #+#              #
#    Updated: 2025/12/13 15:27:25 by ttiprez          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Regles Makefile
MAKEFLAGS += -s

# Compilateur et flags
CC			= cc
CFLAGS		= -Wall -Wextra -g -I$(HEADERS_DIR) -I$(PRINTF_DIR)/include -I$(LIBFT_DIR)

# Nom de l'executable
NAME		= pipex

# Dossiers
SRC_DIR		= src
OBJ_DIR		= obj
HEADERS_DIR	= include
	
# ft_printf
PRINTF_DIR	= ft_printf
PRINTF		= $(PRINTF_DIR)/libftprintf.a

# libft
LIBFT_DIR	= $(PRINTF_DIR)/libft

# Regles
all: $(NAME)

# Creer les dossiers objets
$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)
	@mkdir -p $(OBJ_DIR)/parsing
	@mkdir -p $(OBJ_DIR)/utils
	@mkdir -p $(OBJ_DIR)/execution
	@mkdir -p $(OBJ_DIR)/files

# Compiler ft_printf
$(PRINTF):
	@make -C $(PRINTF_DIR) && echo "$(GREEN)[OK] Compilation ft_printf réussie$(RESET)" || (echo "$(RED)[FAIL] Compilation ft_printf échouée$(RESET)"; exit 1)

# Compiler les fichiers objets
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	@$(CC) $(CFLAGS) -c $< -o $@

# Creer l'executable
$(NAME): $(PRINTF) $(OBJS)
	@$(CC) $(OBJS) $(PRINTF) -o $(NAME) && echo "$(GREEN)[OK] Compilation réussie, exécutable créé$(RESET)" || (echo "$(RED)[FAIL] Compilation échouée$(RESET)"; exit 1)

clean:
	@rm -rf $(OBJ_DIR)
	@make -C $(PRINTF_DIR) clean
	@echo "$(CYAN)Fichiers objets supprimés$(RESET)"

fclean: clean
	@rm -f $(NAME)
	@make -C $(PRINTF_DIR) fclean
	@echo "$(CYAN)Exécutable supprimé$(RESET)"

re: fclean all

.PHONY: all clean fclean re