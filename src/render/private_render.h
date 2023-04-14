/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   private_render.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorbke <lorbke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 14:26:10 by lorbke            #+#    #+#             */
/*   Updated: 2023/04/14 01:31:55 by lorbke           ###   ########.fr       */
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
/* TYPEDEFS																	  */
/* ************************************************************************** */

typedef struct s_start_end
{
	int	start;
	int	end;
}	t_start_end;

typedef struct s_spritehelper
{
	t_start_end	row;
	t_start_end	column;
	t_coor		tex_coor;
	int			temp;
	t_coor		img_coor;
	double		ratio;
	t_hexcolor	color;
}	t_spritehelper;

typedef struct s_sprite
{
	t_vec			dir;
	t_vec			dist;
	t_vec			cam_pos;
	double			img_x;
	int				height;
	int				width;
	t_tex			*tex;
}	t_sprite;

/* ************************************************************************** */
/* FUNCTIONS																  */
/* ************************************************************************** */

// render_hud
void		hud_render(t_game *game);

// render_wall
void		walls_render(t_game *game, int *wall_height);

// render_enemy
void		enemies_render(t_game *game, t_enemy *enemies,
				int *wall_height);

// render_minimap
void		minimap_render(t_game *game);

// render_enemy_utils
void		tex_pixel_to_img(mlx_image_t *img, mlx_texture_t *tex,
				t_coor *tex_coor, t_coor *img_coor);
bool		is_transparent(t_hexcolor color);
void		draw_column(t_sprite *sprite,
				t_spritehelper *hlpr, mlx_image_t *img);
bool		is_visible(t_sprite *sprite, t_spritehelper *hlpr,
				mlx_image_t *img, int *wall_height);
void		row_set_start_end(t_start_end *row, int sprite_height,
				int img_height);
void		column_set_start_end(t_start_end *stripe, int sprite_width,
				int img_width, int img_x);

// render_enemy_sprite
t_hexcolor	convert_to_hexcode(unsigned char r, unsigned char g,
				unsigned char b, unsigned char a);
void		sprite_init(t_sprite *sprite, t_vec *pos, t_tex *tex, t_game *game);

#endif
