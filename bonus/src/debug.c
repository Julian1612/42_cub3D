/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorbke <lorbke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 15:11:10 by lorbke            #+#    #+#             */
/*   Updated: 2023/04/12 19:18:12 by lorbke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h" // cub3D structs
#include "render/private_render.h" // t_sprite
#include "raycast/private_raycast.h" // t_ray
#include "raycast.h" // t_rayhit
#include <stdio.h> // printf

// color codes
#define RESET		"\033[39;49m"
#define BLACK		"\033[30m"
#define RED			"\033[31m"
#define GREEN		"\033[32m"
#define YELLOW		"\033[33m"
#define BLUE		"\033[34m"
#define MAGENTA		"\033[35m"
#define CYAN		"\033[36m"
#define WHITE		"\033[37m"
#define BOLDBLACK	"\033[1m\033[30m"
#define BOLDRED		"\033[1m\033[31m"
#define BOLDGREEN	"\033[1m\033[32m"
#define BOLDYELLOW	"\033[1m\033[33m"
#define BOLDBLUE	"\033[1m\033[34m"
#define BOLDCYAN	"\033[1m\033[36m"
#define BOLDWHITE	"\033[1m\033[37m"

void	debug_print_vec(t_vec *vec, char *str)
{
	if (DEBUG == 0)
		return ;
	printf("%s", str);
	printf("    x: %f\n", vec->x);
	printf("    y: %f\n", vec->y);
}

void	debug_print_player(t_player *player)
{
	if (DEBUG == 0)
		return ;
	printf(BLUE"============ PLAYER ============\n"RESET);
	debug_print_vec(&player->pos, "player position: \n");
	debug_print_vec(&player->dir, "player direction:\n");
}

void	debug_print_ray(t_ray *ray, t_rayhit *hit)
{
	if (DEBUG == 0)
		return ;
	printf(BLUE"============ RAY ============\n"RESET);
	printf("ray angle:   %f\n", ray->angle);
	printf("ray dir x:   %f\n", ray->dir.x);
	printf("ray dir y:   %f\n", ray->dir.y);
	printf("ray origin x:   %f\n", ray->origin.x);
	printf("ray origin y:   %f\n", ray->origin.y);
	printf("map x:   %d\n", ray->map_x);
	printf("map y:   %d\n", ray->map_y);
	printf("step.x:   %f\n", ray->step.x);
	printf("step.y:   %f\n", ray->step.y);
	printf("hypotenuse.x:   %f\n", ray->hypotenuse.x);
	printf("hypotenuse.y:   %f\n", ray->hypotenuse.y);
	printf("length.x:   %f\n", ray->length.x);
	printf("length.y:   %f\n", ray->length.y);
	printf(BLUE"============ HIT ============\n"RESET);
	printf("hit offset:   %f\n", hit->x_offset);
	printf("hit dist:   %f\n", hit->dist);
	printf("hit texture:   %d\n", hit->tex_id);
}

void	debug_print_sprite(t_sprite *sprite)
{
	if (DEBUG == 0)
		return ;
	printf(BLUE"============ SPRITE ============\n"RESET);
	debug_print_vec(&sprite->dir, "sprite direction vector from player:\n");
	debug_print_vec(&sprite->dist, "sprite distance from player:\n");
	debug_print_vec(&sprite->cam_pos, "sprite position on camera plane:\n");
	printf("sprite x position on the screen: %f\n", sprite->img_x);
	printf("sprite.height: %d\n", sprite->height);
	printf("sprite.width: %d\n", sprite->width);
}
