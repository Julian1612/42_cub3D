/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jschneid <jschneid@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 14:00:17 by lorbke            #+#    #+#             */
/*   Updated: 2023/04/14 23:05:04 by jschneid         ###   ########.fr       */
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

#endif
