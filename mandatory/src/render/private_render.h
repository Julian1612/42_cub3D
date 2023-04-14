/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   private_render.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jschneid <jschneid@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 14:26:10 by lorbke            #+#    #+#             */
/*   Updated: 2023/04/14 23:04:43 by jschneid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PRIVATE_RENDER_H
# define PRIVATE_RENDER_H

/* ************************************************************************** */
/* INCLUDES																	  */
/* ************************************************************************** */

# include "../render.h" // t_coor
# include "../types.h" // t_hexcolor
# include "../cub3D.h" // cub3d typedefs

/* ************************************************************************** */
/* FUNCTIONS																  */
/* ************************************************************************** */

// render_wall
void		walls_render(t_game *game, int *wall_height);
void		tex_pixel_to_img(mlx_image_t *img, mlx_texture_t *tex,
				t_coor *tex_coor, t_coor *img_coor);

#endif
