# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lorbke <lorbke@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/01/23 15:19:48 by jschneid          #+#    #+#              #
#    Updated: 2023/04/13 15:46:40 by lorbke           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	cub3D
CFLAGS		=	-g
# -Wall -Wextra -Werror 
LIBMLX		=	./libraries/mlx
LIBFT		=	./libraries/libft
CC			=	cc
VPATH		=	src: src/parser: src/start_screen: \
				src/player_position: src/render src/raycast src/render src/loop

SRC			=	check_for_map.c check_for_rgb.c check_for_texture.c check_map.c \
				check_textures.c error_messages.c get_file_data.c \
				init_player_position.c init_sprite_position.c parser.c \
				parser_utils_0.c parser_utils_1.c \
				init_start_screen.c start_screen.c \
				raycast.c raycast_ray.c raycast_rayhit.c \
				render.c render_wall.c render_hud.c render_enemy.c \
				render_enemy_sprite.c render_enemy_utils.c render_minimap.c \
				loop.c loop_logic.c loop_logic_keys.c loop_logic_switch_state.c \
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
	@$(CC) $(INC) $(LIBS) $(OBJS) -o $(NAME)

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
