# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lorbke <lorbke@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/01/23 15:19:48 by jschneid          #+#    #+#              #
#    Updated: 2023/03/21 14:39:48 by lorbke           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	cub3D
CFLAGS		=   #-O3
# -Wall -Wextra -Werror
LIBMLX		=	./libraries/mlx/
LIBFT		=	./libraries/libft
GARBAGE		=	./libraries/garbage_collector
CC			=	cc
VPATH		=	src: src/parser: src/parser/get_map: src/parser/get_textures: \

SRC			=	main.c \
				parser.c check_for_map.c check_for_rgb.c parser_utils.c \
				check_textures.c check_for_texture.c error_messages.c \
				get_file_data.c check_map.c init_player_position.c \
				debug.c errexit.c hook.c initialize.c raycaster.c render.c utils.c

HEADERS		= -I ./include -I $(LIBMLX)/include/MLX42 -I $(LIBFT)
LIBS		= -lglfw -L$(shell brew --prefix glfw)/lib $(LIBMLX)/libmlx42.a $(LIBFT)/libft.a
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
	@$(CC) $(OBJS) $(LIBS) $(HEADERS) -Wno-gnu-include-next -I./LeakSanitizer/include -o cub3D

n: obj $(OBJS)
	@$(CC) $(OBJS) $(LIBS) $(HEADERS)
#  -Wno-gnu-include-next -I./LeakSanitizer/include -L./LeakSanitizer -llsan -lc++-o $(NAME)

clean:
	@rm -rf obj
	@$(MAKE) -C $(LIBFT) clean
	@$(MAKE) -C $(LIBMLX) clean

fclean: clean
	@rm -f $(NAME)
	@$(MAKE) -C $(LIBFT) fclean
	@$(MAKE) -C $(LIBMLX) fclean

re: clean all

debug: CFLAGS += -O0 -DDEBUG=1 -g
debug: clean all
	@$(MAKE) clean

.PHONY: all, clean, fclean, re, libmlx, libft
