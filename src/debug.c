/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorbke <lorbke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 15:11:10 by lorbke            #+#    #+#             */
/*   Updated: 2023/03/10 15:24:29 by lorbke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h" // cub3D structs
#include <stdio.h> // printf

// colors for printf
# define RESET       "\033[39;49m"
# define BLACK       "\033[30m"        /* Black */
# define RED         "\033[31m"        /* Red */
# define GREEN       "\033[32m"        /* Green */
# define YELLOW      "\033[33m"        /* Yellow */
# define BLUE        "\033[34m"        /* Blue */
# define MAGENTA     "\033[35m"        /* Magenta */
# define CYAN        "\033[36m"        /* Cyan */
# define WHITE       "\033[37m"        /* White */
# define BOLDBLACK   "\033[1m\033[30m" /* Bold Black */
# define BOLDRED     "\033[1m\033[31m" /* Bold Red */
# define BOLDGREEN   "\033[1m\033[32m" /* Bold Green */
# define BOLDYELLOW  "\033[1m\033[33m" /* Bold Yellow */
# define BOLDBLUE    "\033[1m\033[34m" /* Bold Blue */
# define BOLDMAGENTA "\033[1m\033[35m" /* Bold Magenta */
# define BOLDCYAN    "\033[1m\033[36m" /* Bold Cyan */
# define BOLDWHITE   "\033[1m\033[37m" /* Bold White */

void	debug_print_game(t_game *game)
{
	// player
	printf(BLUE"============ PLAYER ============\n"RESET);
	printf("player x:   %d\n", game->player.x);
	printf("player y:   %d\n", game->player.y);
	printf("player dir: %f\n", game->player.view_dir);
	printf("\n");
}
