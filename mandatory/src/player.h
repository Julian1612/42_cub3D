/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jschneid <jschneid@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 15:49:01 by lorbke            #+#    #+#             */
/*   Updated: 2023/04/14 23:10:17 by jschneid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PLAYER_H
# define PLAYER_H

/* ************************************************************************** */
/* INCLUDES																	  */
/* ************************************************************************** */

# include "types.h" // t_vec
# include <stdbool.h> // bool

/* ************************************************************************** */
/* TYPEDEFS																	  */
/* ************************************************************************** */

// avoid circular dependency
typedef struct s_game	t_game;
typedef struct s_map	t_map;

typedef struct s_player
{
	t_vec			pos;
	t_vec			cplane;
	t_vec			dir;
	double			mov_speed;
	double			rot_speed;
}	t_player;

/* ************************************************************************** */
/* FUNCTIONS																  */
/* ************************************************************************** */

// player
void	player_move(t_vec *pos, t_map *map, double x_offset, double y_offset);
void	player_rotate(t_player *player, double rot_speed);

#endif
