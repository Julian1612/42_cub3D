/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorbke <lorbke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 15:49:01 by lorbke            #+#    #+#             */
/*   Updated: 2023/04/13 14:39:22 by lorbke           ###   ########.fr       */
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

// avoid circular dependency
typedef struct s_game	t_game;

typedef struct s_weapon
{
	char			damage;
	char			range;
	char			reload_time;
	double			last_frame_time;
	enum e_tex_id	curr_frame;
}	t_weapon;

typedef struct s_player
{
	t_vec			pos;
	t_vec			cplane;
	t_vec			dir;
	int				health;
	double			mov_speed;
	double			rot_speed;
	t_weapon		*weapon;
}	t_player;

/* ************************************************************************** */
/* FUNCTIONS																  */
/* ************************************************************************** */

// player
void	player_shoot(t_player *player, t_enemy *enemies, t_game *game);
void	player_move(t_vec *pos, t_map *map, double x_offset, double y_offset);
void	player_rotate(t_player *player, double rot_speed);

#endif
