/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorbke <lorbke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 15:11:10 by lorbke            #+#    #+#             */
/*   Updated: 2023/03/12 17:35:28 by lorbke           ###   ########.fr       */
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
	printf("\n");
}

void	debug_print_coor(t_coor *coor)
{
	printf("x:   %f\n", coor->x);
	printf("y:   %f\n", coor->y);
	printf("\n");
}

void	debug_print_ray(t_ray *ray)
{
	printf(BLUE"============ RAY ============\n"RESET);
	printf("vec x cross:\n");
	debug_print_coor(&ray->nx_latitude);
	printf("vec y cross:\n");
	debug_print_coor(&ray->nx_longitude);
	printf("ray dir: %f\n", ray->dir);
	printf("\n");
}
