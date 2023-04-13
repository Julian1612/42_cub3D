/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enemy.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorbke <lorbke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 15:31:24 by lorbke            #+#    #+#             */
/*   Updated: 2023/04/13 15:51:03 by lorbke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENEMY_H
# define ENEMY_H

/* ************************************************************************** */
/* INCLUDES																	  */
/* ************************************************************************** */

# include "types.h" // t_vec
# include <stdbool.h> // bool

/* ************************************************************************** */
/* TYPEDEFS																	  */
/* ************************************************************************** */

typedef struct s_map	t_map;
typedef struct s_player	t_player;

typedef struct s_enemy
{
	bool			alive;
	t_vec			pos;
	char			health;
	double			speed;
	char			damage;
	double			last_frame_time;
	enum e_tex_id	curr_frame;
}	t_enemy;

/* ************************************************************************** */
/* FUNCTIONS																  */
/* ************************************************************************** */

// enemy
void	enemy_move(t_enemy *enemy, t_map *map, t_vec offset, int enemy_index);
void	enemy_attack(t_player *player, t_enemy *enemy);
void	enemy_die(t_enemy *enemy, t_map *map, int enemy_index);

#endif
