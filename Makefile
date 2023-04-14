# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jschneid <jschneid@student.42heilbronn.    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/01/23 15:19:48 by jschneid          #+#    #+#              #
#    Updated: 2023/04/14 01:58:12 by jschneid         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	cub3D
CFLAGS		=	-g -Wall -Wextra -Werror #-fsanitize=address,undefinded
LIBMLX		=	./libraries/mlx
LIBFT		=	./libraries/libft
CC			=	cc
VPATH		=	src: src/parser: src/start_screen: \
				src/player_position: src/render src/raycast src/render src/loop

SRC			=	parser.c parser_check_for_map.c parser_check_for_rgb.c parser_check_for_texture.c parser_check_map.c parser_check_textures.c parser_error_messages.c parser_get_file_data.c parser_init_player_position.c parser_init_sprite_position.c \
				parser_utils_0.c parser_utils_1.c \
				init_start_screen.c start_screen.c \
				raycast.c raycast_ray.c raycast_rayhit.c \
				render.c render_wall.c render_hud.c render_enemy.c \
				render_enemy_sprite.c render_enemy_utils.c render_minimap.c \
				loop.c loop_logic.c loop_logic_keys.c loop_logic_door.c \
				loop_graphic.c \
				collision.c debug.c initialize.c errexit.c math.c time.c \
				player.c enemy.c utils.c main.c

INC			=	-I./src -I$(LIBMLX)/include/MLX42 -I$(LIBFT)/src/libft
HEADERS		=	cub3D.h raycast.h render.h raycast/private_raycast.h \
				render/private_render.h
LIBS		=	-lglfw -L$(shell brew --prefix glfw)/lib $(LIBMLX)/libmlx42.a $(LIBFT)/libft.a
OBJS		=	$(addprefix $(OBJ_DIR),$(SRC:.c=.o))
OBJ_DIR		=	./obj/

BOLD		=	\033[1m
BLACK		=	\033[30;1m
RED			=	\033[31;1m
GREEN		=	\033[32;1m
YELLOW		=	\033[33;1m
BLUE		=	\033[34;1m
MAGENTA		=	\033[35;1m
CYAN		=	\033[36;1m
WHITE		=	\033[37;1m
RESET		=	\033[0m

all: libft $(NAME)

obj:
	@mkdir -p $(OBJ_DIR)

libft:
	@$(MAKE) -C $(LIBFT)

$(NAME): obj $(OBJS)
	@$(CC) $(CFLAGS) $(INC) $(LIBS) $(OBJS) -o $(NAME)

obj/%.o: %.c $(HEADERS)
	@$(CC) $(CFLAGS) -o $@ -c $<
	@printf "$(GREEN)$(BOLD)\rCompiling: $(notdir $<)\r\e[35C[OK]\n$(RESET)"

clean:
	@rm -rf obj

fclean: clean
	@rm -f $(NAME)
	@$(MAKE) -C $(LIBFT) fclean
	@$(MAKE) -C $(LIBMLX) fclean

re: clean all

debug: CFLAGS += -O0 -DDEBUG=1 -g
debug: clean all
	@$(MAKE) clean

.PHONY: all, clean, fclean, re, libmlx, libft
