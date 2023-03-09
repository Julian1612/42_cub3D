# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lorbke <lorbke@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/01/23 15:19:48 by jschneid          #+#    #+#              #
#    Updated: 2023/03/09 19:46:32 by lorbke           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	cub3D
CFLAGS		=   -g
# -Wall -Wextra -Werror 
LIBMLX		=	./libraries/MLX
LIBFT		=	./libraries/libft
CC			=	cc
VPATH		=	src: src/parser: src/parser/get_map: src/parser/get_textures: \
				src/player_position:

SRC			=	errexit.c game_loop.c main.c \
				check_args.c check_file.c error_messages.c parser.c put_file_content_in_arr.c \
				errors_textures.c free_textures.c get_path_utils.c get_path.c get_rgb_values.c \
				get_textures.c \
				check_map.c check_wall_horizontal.c check_wall_vertical.c errors_map.c get_map.c \
				malloc_map.c map_to_arr.c\
				init_player_position.c

HEADERS		= -I ./include -I $(LIBMLX)/include/MLX42 -I $(LIBFT)
LIBS		= -lglfw -L /Users/$(USER)/goinfre/.brew/opt/glfw/lib/ $(LIBMLX)/libmlx42.a $(LIBFT)/libft.a
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
