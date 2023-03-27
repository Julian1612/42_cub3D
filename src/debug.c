/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorbke <lorbke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 15:11:10 by lorbke            #+#    #+#             */
/*   Updated: 2023/03/27 23:22:55 by lorbke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h" // cub3D structs
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

void	debug_print_player(t_player *player)
{
	printf(BLUE"============ PLAYER ============\n"RESET);
	printf("player x:   %f\n", player->x);
	printf("player y:   %f\n", player->y);
	printf("player dir: %f\n", player->view_dir);
}

void	debug_print_coor(t_coor *coor)
{
	printf("x:   %f\n", coor->x);
	printf("y:   %f\n", coor->y);
}

void	debug_print_ray(t_ray *ray)
{
	if (DEBUG == 0)
		return ;
	printf(BLUE"============ RAY ============\n"RESET);
	printf("ray dir x:   %f\n", ray->dir.x);
	printf("ray dir y:   %f\n", ray->dir.y);
	printf("ray origin x:   %f\n", ray->origin.x);
	printf("ray origin y:   %f\n", ray->origin.y);
	printf("map x:   %d\n", ray->map_x);
	printf("map y:   %d\n", ray->map_y);
	printf("step.x:   %f\n", ray->step.x);
	printf("step.y:   %f\n", ray->step.y);
	printf("op_step.x:   %f\n", ray->op_step.x);
	printf("op_step.y:   %f\n", ray->op_step.y);
	printf("hypotenuse.x:   %f\n", ray->hypotenuse.x);
	printf("hypotenuse.y:   %f\n", ray->hypotenuse.y);
	printf("length.x:   %f\n", ray->length.x);
	printf("length.y:   %f\n", ray->length.y);
}
