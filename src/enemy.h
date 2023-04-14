/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enemy.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorbke <lorbke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 15:31:24 by lorbke            #+#    #+#             */
/*   Updated: 2023/04/14 03:16:29 by lorbke           ###   ########.fr       */
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
	t_frame			frame;
}	t_enemy;

/* ************************************************************************** */
/* FUNCTIONS																  */
/* ************************************************************************** */

// enemy
void	enemy_move(t_enemy *enemy, t_map *map, t_vec offset, int enemy_index);
void	enemy_attack(t_player *player, t_enemy *enemy);
void	enemy_die(t_enemy *enemy);

#endif
