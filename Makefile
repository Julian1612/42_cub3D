# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jschneid <jschneid@student.42heilbronn.    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/01/23 15:19:48 by jschneid          #+#    #+#              #
#    Updated: 2023/04/09 19:06:20 by jschneid         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	cub3D
CFLAGS		=   -g
# -Wall -Wextra -Werror
LIBMLX		=	./libraries/mlx
LIBFT		=	./libraries/libft
GARBAGE		=	./libraries/garbage_collector
CC			=	cc
VPATH		=	src: src/parser: \

SRC			=	debug.c errexit.c hook.c initialize.c main.c \
				minimap.c mouse_movements.c raycaster.c \
				render.c start_screen.c utils.c \
				check_for_map.c check_for_rgb.c check_for_texture.c \
				check_map.c check_textures.c error_messages.c get_file_data.c\
				init_player_position.c parser_utils_0.c parser_utils_1.c \
				parser.c

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

all: libft $(NAME)

obj:
	@mkdir -p $(OBJ_DIR)

libft:
	@$(MAKE) -C $(LIBFT)

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
