/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorbke <lorbke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 14:00:17 by lorbke            #+#    #+#             */
/*   Updated: 2023/04/12 18:52:44 by lorbke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEBUG_H
# define DEBUG_H

/* ************************************************************************** */
/* INCLUDES																	  */
/* ************************************************************************** */

# include "cub3D.h" // cub3d typedefs
# include "render/private_render.h" // t_sprite
# include "raycast/private_raycast.h" // raycast typedefs
# include "raycast.h" // raycast typedefs

/* ************************************************************************** */
/* FUNCTIONS																  */
/* ************************************************************************** */

// debug
void			debug_print_vec(t_vec *vec, char *str);
void			debug_print_player(t_player *player);
void			debug_print_ray(t_ray *ray, t_rayhit *hit);
void			debug_print_sprite(t_sprite *sprite);

#endif
