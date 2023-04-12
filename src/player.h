/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorbke <lorbke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 15:49:01 by lorbke            #+#    #+#             */
/*   Updated: 2023/04/12 16:15:45 by lorbke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PLAYER_H
# define PLAYER_H

/* ************************************************************************** */
/* INCLUDES																	  */
/* ************************************************************************** */

# include "enemy.h" // t_enemy
# include "types.h" // t_vec
# include <stdbool.h> // bool

/* ************************************************************************** */
/* TYPEDEFS																	  */
/* ************************************************************************** */

typedef struct s_game	t_game;

typedef struct s_player
{
	t_vec			pos;
	t_vec			cplane;
	t_vec			dir;
	int				health;
	t_weapon		*weapon;
}	t_player;

/* ************************************************************************** */
/* FUNCTIONS																  */
/* ************************************************************************** */

// player
void	player_shoot(t_player *player, t_enemy *enemies, t_game *game);
void	player_move(t_vec *pos, t_map *map, double x_offset, double y_offset);
void	player_rotate(t_player *player, double rot_speed, bool left);

#endif
