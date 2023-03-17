# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jschneid <jschneid@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/01/23 15:19:48 by jschneid          #+#    #+#              #
#    Updated: 2023/03/17 10:29:56 by jschneid         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	cub3D
CFLAGS		=   -g
# -Wall -Wextra -Werror
LIBMLX		=	./libraries/MLX
LIBFT		=	./libraries/libft
GARBAGE		=	./libraries/garbage_collector
CC			=	cc
VPATH		=	src: src/parser: src/parser/get_map: src/parser/get_textures: \

SRC			=	main.c \
				parser.c check_for_map.c check_for_rgb.c \
				check_textures.c check_for_texture.c error_messages.c \
				get_file_data.c check_map.c init_player_position.c \

HEADERS		= -I ./include -I $(LIBMLX)/include/MLX42 -I $(LIBFT)
LIBS		= -lglfw -L /Users/$(USER)/goinfre/.brew/opt/glfw/lib/ $(LIBMLX)/libmlx42.a $(LIBFT)/libft.a
# $(GARBAGE)/libwastewiz.a
OBJS		= $(addprefix $(OBJ_DIR),$(SRC:.c=.o))
OBJ_DIR		= ./obj/

BOLD		= \033[1m
BLACK		= \033[30;1m
RED			= \033[31;1m
GREEN		= \033[32;1m
YELLOW		= \033[33;1m
BLUE		= \033[34;1m
MAGENTA		= \033[35;1m
CYAN		= \033[36;1m
WHITE		= \033[37;1m
RESET		= \033[0m

all: libft libmlx $(NAME)

obj:
	@mkdir -p $(OBJ_DIR)

libft:
	@$(MAKE) -C $(LIBFT)

libmlx:
	@$(MAKE) -C $(LIBMLX)

# garbage_collector:
# 	@$(MAKE) -C $(GARBAGE)

obj/%.o: %.c
	@$(CC) $(CFLAGS) -o $@ -c $< $(HEADERS) && printf "$(GREEN)$(BOLD)\rCompiling: $(notdir $<)\r\e[35C[OK]\n$(RESET)"

$(NAME): obj $(OBJS)
	@$(CC) $(OBJS) $(LIBS) $(HEADERS) -o $(NAME)

n: obj $(OBJS)
	@$(CC) $(OBJS) $(LIBS) $(HEADERS) -o $(NAME)

clean:
	@rm -rf obj
	@$(MAKE) -C $(LIBFT) clean
	@$(MAKE) -C $(LIBMLX) clean

fclean: clean
	@rm -f $(NAME)
	@$(MAKE) -C $(LIBFT) fclean
	@$(MAKE) -C $(LIBMLX) fclean

re: clean all

.PHONY: all, clean, fclean, re, libmlx, libft
