# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jschneid <jschneid@student.42heilbronn.    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/01/23 15:19:48 by jschneid          #+#    #+#              #
#    Updated: 2023/04/14 15:26:17 by jschneid         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	cub3D
CFLAGS		=	-g -O3 -Wall -Wextra -Werror #-fsanitize=address,undefined
LIBMLX		=	./libraries/mlx
LIBFT		=	./libraries/libft
CC			=	cc
VPATH		=	src: src/parser: \
				src/player_position: src/render src/raycast src/render src/loop

SRC			=	parser.c parser_check_for_map.c parser_check_for_rgb.c \
				parser_check_for_texture.c parser_check_map.c \
				parser_check_textures.c parser_error_messages.c \
				parser_get_file_data.c parser_init_player_position.c \
				parser_init_sprite_position.c \
				parser_utils_0.c parser_utils_1.c \
				raycast.c raycast_ray.c raycast_rayhit.c \
				render.c render_wall.c render_hud.c render_enemy.c render_utils.c \
				render_enemy_sprite.c render_enemy_utils.c render_minimap.c \
				loop.c loop_screen.c loop_logic.c loop_logic_keys.c \
				loop_logic_door.c loop_graphic.c \
				collision.c debug.c initialize.c errexit.c math.c time.c \
				player.c enemy.c utils.c sound.c main.c

INC			=	-I./src -I$(LIBMLX)/include/MLX42 -I$(LIBFT)/src/libft
HEADERS		=	cub3D.h raycast.h render.h raycast/private_raycast.h \
				render/private_render.h
LIBS		=	-lglfw -L$(shell brew --prefix glfw)/lib $(LIBMLX)/build/libmlx42.a $(LIBFT)/libft.a
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

all: libmlx libft $(NAME)

obj:
	@mkdir -p $(OBJ_DIR)

libft:
	@if [ ! -f $(LIBFT)/libft.a ]; then \
		printf "$(GREEN)Building libft: $(RESET)"; \
		mkdir -p $(LIBFT)/build; \
		$(MAKE) -C $(LIBFT) >/dev/null; \
		printf "$(GREEN)✅$(RESET)\n"; \
	fi

libmlx:
	@if [ ! -f $(LIBMLX)/build/libmlx42.a ]; then \
		printf "$(GREEN)Building MLX42: $(RESET)"; \
		mkdir -p $(LIBMLX)/build; \
		cmake $(LIBMLX) -B $(LIBMLX)/build >/dev/null 2>&1 && make -C $(LIBMLX)/build -j4 >/dev/null 2>&1; \
		printf "$(GREEN)✅$(RESET)\n"; \
	fi

$(NAME): obj $(OBJS)
	@echo "$(GREEN)cub3D Compiled ✅$(RESET)";
	@$(CC) $(CFLAGS) $(INC) $(LIBS) $(OBJS) -o $(NAME)

obj/%.o: %.c $(HEADERS)
	@$(CC) $(CFLAGS) -o $@ -c $<

clean:
	@echo "$(RED)Cleaning ... $(RESET)"
	@$(MAKE) -C $(LIBFT) clean >/dev/null
	@if [ -f $(LIBMLX)/build ]; then \
		@$(MAKE) -C $(LIBMLX)/build clean >/dev/null;\
	fi
	@rm -rf $(OBJ_DIR)

fclean: clean
	@$(MAKE) -C $(LIBFT) fclean >/dev/null
	@rm -rf $(LIBMLX)/build
	@rm -f $(NAME)

re: fclean all

debug: CFLAGS += -O0 -DDEBUG=1 -g
debug: clean all
	@$(MAKE) clean

.PHONY: all, clean, fclean, re, libmlx, libft
