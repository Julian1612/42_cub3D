/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   types.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorbke <lorbke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 15:55:32 by lorbke            #+#    #+#             */
/*   Updated: 2023/04/14 03:17:50 by lorbke           ###   ########.fr       */
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
	DOOR_FRONT,
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
	HUD_GUN1,
	HUD_GUN2,
	HUD_GUN3,
	HUD_GUN4,
	HUD_GUN5,
	HUD_GUN6,
	HUD_HEART,
	START_BG1,
	START_BG2,
	START_BG3,
	START_BG4,
	START_BG5,
	START_BG6,
	START_BG7,
	START_BG8,
	LAST,
};

/* ************************************************************************** */
/* TYPEDEFS																	  */
/* ************************************************************************** */

typedef uint32_t	t_hexcolor;
typedef uint8_t		t_subpxl;

typedef struct s_texture
{
	char			*path;
	mlx_texture_t	*tex;
}	t_tex;

typedef struct s_vector
{
	double	x;
	double	y;
}	t_vec;

typedef struct s_frame
{
	double			time_of_last;
	enum e_tex_id	curr;
}	t_frame;

#endif
