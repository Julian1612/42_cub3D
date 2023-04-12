/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   types.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorbke <lorbke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 15:55:32 by lorbke            #+#    #+#             */
/*   Updated: 2023/04/12 16:04:25 by lorbke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TYPES_H
# define TYPES_H

/* ************************************************************************** */
/* INCLUDES																	  */
/* ************************************************************************** */

# include "../libraries/mlx/include/MLX42/MLX42.h" // mlx typedefs
# include <stdbool.h> // bool

/* ************************************************************************** */
/* ENUMS																	  */
/* ************************************************************************** */

enum e_tex_id
{
	NORTH,
	EAST,
	SOUTH,
	WEST,
	KNIGHT,
	LAMP,
	TABLE,
	DOOR_FRONT,
	DOOR_SIDE,
	GUN1,
	GUN2,
	GUN3,
	GUN4,
	GUN5,
	GUN6,
	ZOMBIE_RUN1,
	ZOMBIE_RUN2,
	ZOMBIE_RUN3,
	ZOMBIE_LEFT1,
	ZOMBIE_LEFT2,
	ZOMBIE_LEFT3,
	ZOMBIE_RIGHT1,
	ZOMBIE_RIGHT2,
	ZOMBIE_RIGHT3,
	ZOMBIE_DEAD1,
	ZOMBIE_DEAD2,
	ZOMBIE_DEAD3,
	ZOMBIE_DEAD4,
	ZOMBIE_DEAD5,
	ZOMBIE_DEAD6,
	ZOMBIE_DEAD7,
	ZOMBIE_DEAD8,
};

/* ************************************************************************** */
/* TYPEDEFS																	  */
/* ************************************************************************** */

typedef uint32_t	t_hexcolor;
typedef uint8_t		t_subpxl;

typedef struct s_vector
{
	double	x;
	double	y;
}	t_vec;

typedef struct s_weapon
{
	char			damage;
	char			range;
	char			reload_time;
	double			last_frame_time;
	enum e_tex_id	curr_frame;
}	t_weapon;

#endif
