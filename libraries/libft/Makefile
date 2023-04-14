# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jschneid <jschneid@student.42heilbronn.    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/02/10 10:08:16 by jschneid          #+#    #+#              #
#    Updated: 2023/04/14 15:07:09 by jschneid         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# SHELL macro
SHELL  := /bin/bash

# colors
RED    := \033[0;31m
GREEN  := \033[0;32m
YELLOW := \033[0;33m
BLUE   := \033[0;34m
RESET  := \033[0m

# name macro
NAME   := libft.a

# command macros
CC        := cc
AR        := ar rcs
RM        := rm -f
ADD_FLAGS := #-g -fsanitize=address,undefined
CFLAGS    := -Wall -Wextra -Werror

# VPATH
VPATH	  := src src/ft_printf src/get_next_line src/libft

# src and obj files macros
SRC_PATH  := src
OBJ_PATH  := obj
SRC       := ft_printf.c ft_printf_characters.c \
			 ft_printf_hexadecimal.c ft_printf_numbers.c \
			 ft_printf_percent.c ft_printf_pointer.c ft_printf_string.c \
			 ft_printf_utils_00.c ft_printf_utils_01.c \
			 get_next_line.c get_next_line_bonus.c \
			 get_next_line_utils.c \
			 ft_arrlen.c ft_atoi.c ft_bzero.c ft_calloc.c ft_free_arr.c \
			 ft_isalnum.c ft_isalpha.c ft_isascii.c ft_isdigit.c ft_isprint.c \
			 ft_itoa.c ft_lstadd_back.c ft_lstadd_front.c ft_lstclear.c \
			 ft_lstdelone.c ft_lstiter.c ft_lstlast.c ft_lstmap.c ft_lstnew.c \
			 ft_lstsize.c ft_memchr.c ft_memcmp.c ft_memcpy.c ft_memmove.c \
			 ft_memset.c ft_putchar_fd.c ft_putendl_fd.c ft_putnbr_fd.c \
			 ft_putstr_fd.c ft_split.c ft_strchr.c ft_strcpy.c ft_strdup.c \
			 ft_striteri.c ft_strjoin.c ft_strlcat.c ft_strlcpy.c ft_strlen.c \
			 ft_strmapi.c ft_strncmp.c ft_strnstr.c ft_strrchr.c ft_strtrim.c \
			 ft_substr.c ft_tolower.c ft_toupper.c
OBJ       := $(SRC:%.c=$(OBJ_PATH)/%.o)

###################################
#	SYSTEM SPECIFIC SETTINGS	  #
###################################

ifeq ($(shell uname -s), Linux)
	CFLAGS += -D LINUX -Wno-unused-result
endif

###################################
#	RULES						  #
###################################

all: $(NAME)

$(NAME): $(OBJ_PATH) $(OBJ)
	@echo -e -n "$(BLUE)Creating: libft library: $(RESET)"
	$(AR) $(NAME) $(OBJ)
	@echo -e "$(GREEN)make: libft success!$(RESET)"

$(OBJ_PATH):
	@mkdir -p $(OBJ_PATH)

$(OBJ_PATH)/%.o: %.c
	@echo -e -n "$(YELLOW)Compiling: $(RESET)"
	$(CC) $(CFLAGS) $(ADD_FLAGS) -I. -c $< -o $@

clean:
	@$(RM) -r $(OBJ_PATH)

fclean: clean
	@$(RM) $(NAME)
	@echo -e "$(RED)make: libft cleaned!$(RESET)"

re: fclean all

.PHONY: all clean fclean re
