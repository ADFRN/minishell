# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ttiprez <ttiprez@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/03/05 15:56:04 by afournie          #+#    #+#              #
#    Updated: 2026/03/10 14:49:48 by ttiprez          ###   ########.fr        #
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

# --- CONFIG ---
CC      = cc
CFLAGS  = -Wall -Wextra -Werror
RM      = rm -f
AR      = ar rcs
NAME    = libft.a

SRCS    = ft_atoi.c ft_itoa.c ft_bzero.c ft_split.c ft_lstnew.c ft_memcmp.c \
          ft_memset.c ft_memcpy.c ft_printf.c ft_putnbr.c ft_putstr.c \
          ft_strchr.c ft_strlen.c ft_substr.c ft_lstmap.c ft_memchr.c \
          ft_strdup.c ft_calloc.c ft_strjoin.c ft_strnstr.c ft_lstlast.c \
          ft_lstsize.c ft_isalnum.c ft_isdigit.c ft_memmove.c ft_strlcat.c \
          ft_strmapi.c ft_strrchr.c ft_tolower.c ft_isalpha.c ft_isprint.c \
          ft_lstiter.c ft_isascii.c ft_strlcpy.c ft_strncmp.c ft_strtrim.c \
          ft_toupper.c ft_lstclear.c ft_striteri.c ft_putnbr_fd.c \
          ft_lstdelone.c ft_putstr_fd.c ft_putchar_fd.c ft_putendl_fd.c \
          ft_putnbr_hexa.c ft_lstadd_back.c ft_lstadd_front.c 	\
		  ft_get_next_line.c ft_strcpy.c ft_strcat.c ft_strnjoin.c ft_strndup.c

OBJS    = $(SRCS:.c=.o)
TOTAL_FILES := $(words $(SRCS))
CURRENT_FILE = 0

# --- RULES ---

all: $(NAME)

$(NAME): $(OBJS)
	@$(AR) $(NAME) $(OBJS)
	@echo "$(GREEN)$(NAME) est compilé avec succès !           $(RESET)"

%.o: %.c
	@$(eval CURRENT_FILE=$(shell echo $$(($(CURRENT_FILE) + 1))))
	@printf "$(BLUE)Compiling [%d/%d] $(RESET) %-25s\r" $(CURRENT_FILE) $(TOTAL_FILES) $<
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@$(RM) $(OBJS)
	@echo "$(RED)Objets nettoyés.$(RESET)"

fclean: clean
	@$(RM) $(NAME)
	@echo "$(RED)$(NAME) supprimé.$(RESET)"

re: fclean all

.PHONY: all clean fclean re
