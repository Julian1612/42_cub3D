/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   private_raycast.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorbke <lorbke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 13:14:13 by lorbke            #+#    #+#             */
/*   Updated: 2023/04/12 14:03:47 by lorbke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PRIVATE_RAYCAST_H
# define PRIVATE_RAYCAST_H

/* ************************************************************************** */
/* INCLUDES																	  */
/* ************************************************************************** */

# include "../cub3D.h" // t_vec
# include "../raycast.h" // t_rayhit

/* ************************************************************************** */
/* TYPEDEFS																	  */
/* ************************************************************************** */

typedef struct s_ray
{
	double	angle;
	t_vec	dir;
	t_vec	origin;
	int		map_x;
	int		map_y;
	t_vec	step;
	t_vec	hypotenuse;
	t_vec	length;
	bool	y_side;
}				t_ray;

/* ************************************************************************** */
/* FUNCTIONS																  */
/* ************************************************************************** */

// rayhit
void	rayhit_set_type(t_rayhit *hit, t_ray *ray, t_map *map, char target);
void	rayhit_set_tex_id(t_rayhit *hit, bool y_side, t_vec *step);
void	rayhit_set_offset(t_rayhit *hit, bool y_side, t_ray *ray);
void	rayhit_init(t_rayhit *hit);

// ray
void	ray_set_distance(t_rayhit *hit, t_ray *ray, bool y_side);
double	ray_get_y_offset(t_ray *ray);
double	ray_get_x_offset(t_ray *ray);
void	ray_init(t_ray *ray, t_vec *pos, t_vec *ray_dir);

#endif
