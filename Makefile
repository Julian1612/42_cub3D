# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lorbke <lorbke@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/01/23 15:19:48 by jschneid          #+#    #+#              #
#    Updated: 2023/04/12 18:30:36 by lorbke           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	cub3D
CFLAGS		=	-g
# -Wall -Wextra -Werror 
LIBMLX		=	./libraries/mlx
LIBFT		=	./libraries/libft
CC			=	cc
VPATH		=	src: src/parser: src/parser/get_map: src/parser/get_textures: \
				src/player_position: src/render src/raycast src/render src/loop

SRC			=	raycast.c raycast_ray.c raycast_rayhit.c \
				render.c render_wall.c render_hud.c render_enemy.c \
				render_enemy_sprite.c render_enemy_utils.c \
				loop.c loop_logic.c loop_logic_door.c loop_graphic.c \
				collision.c debug.c initialize.c \
				errexit.c utils.c time.c enemy.c player.c main.c

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
