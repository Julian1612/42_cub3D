/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorbke <lorbke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 15:09:20 by lorbke            #+#    #+#             */
/*   Updated: 2023/04/14 06:24:29 by lorbke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RENDER_H
# define RENDER_H

/* ************************************************************************** */
/* INCLUDES																	  */
/* ************************************************************************** */

# include "cub3D.h" // cub3d typedefs

/* ************************************************************************** */
/* TYPEDEFS																	  */
/* ************************************************************************** */

typedef struct s_coor
{
	int		x;
	int		y;
}	t_coor;

/* ************************************************************************** */
/* FUNCTIONS																  */
/* ************************************************************************** */

// render
void	render_game(t_game *game);

// render_utils
void	render_texture(mlx_image_t *img, t_tex *tex,
			t_coor pos, double ratio);
void	render_texture_transparent(mlx_image_t *img, t_tex *tex,
			t_coor pos, double ratio);
void	render_color_image(mlx_image_t *img, t_hexcolor color);

#endif
