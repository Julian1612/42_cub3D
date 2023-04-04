/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorbke <lorbke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 17:04:16 by jschneid          #+#    #+#             */
/*   Updated: 2023/04/03 15:49:52 by lorbke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

/* ************************************************************************** */
/* INCLUDES																	  */
/* ************************************************************************** */

# include "../libraries/mlx/include/MLX42/MLX42.h" // mlx typedefs

/* ************************************************************************** */
/* DEFINES																	  */
/* ************************************************************************** */

# define WIDTH 400
# define HEIGHT 400
# define ERROR -1
# define SUCCESS 0
# define MM_BLOCK_SIZE 64
# define WALL '1'
# define FPS 60

# ifndef DEBUG
#  define DEBUG 0
# endif

/* ************************************************************************** */
/* ENUMS																	  */
/* ************************************************************************** */

enum e_tex_id
{
	NORTH,
	EAST,
	SOUTH,
	WEST,
	DOOR,
	SPRITE,
};

/* ************************************************************************** */
/* TYPEDEFS																	  */
/* ************************************************************************** */

typedef uint32_t	t_hexcolor;

typedef struct s_vector
{
	double	x;
	double	y;
}	t_vec;

typedef struct s_texture
{
	char			*path;
	mlx_texture_t	*tex;
}	t_tex;

typedef struct s_object
{
	t_vec			pos;
	t_tex			*tex;
	double			y_offset;
	enum e_obj_id
	{
		DECOR,
		WEAPON,
		COIN,
	}	id;
}	t_object;

// @note ammunition is not implemented
typedef struct s_weapon
{
	t_tex			*tex;
	char			*damage;
	char			*range;
	char			*reload_time;
}	t_weapon;

// @note enemies are always oriented towards the player
typedef struct s_enemy
{
	t_vec			pos;
	t_tex			*tex;
	char			health;
	char			*speed;
	t_weapon		weapon;
}	t_enemy;

typedef struct s_minimap
{
	t_vec			pos;
	double			width;
	double			height;
	mlx_image_t		*player;
	mlx_image_t		*walls;
	mlx_image_t		*view_dir;
}	t_minimap;

typedef struct s_map
{
	char		**map;
	t_tex		*textures;
	t_object	*objs;
	t_enemy		*enemies;
	t_hexcolor	ceiling_color;
	t_hexcolor	floor_color;
}	t_map;

// @note weapon is pointer because the player can change weapons
typedef struct s_player
{
	t_vec			pos;
	t_vec			cplane;
	t_vec			dir;
	t_weapon		*weapon;
}	t_player;

// @note items might be added here
typedef struct s_game
{
	mlx_t			*mlx;
	mlx_image_t		*img_a;
	mlx_image_t		*img_b;
	t_map			map;
	t_minimap		minimap;
	t_player		player;
	t_enemy			*enemies;
}	t_game;

// @todo move to raycaster header
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

typedef struct s_rayhit
{
	double			stripe;
	double			dist;
	enum e_tex_id	tex_id;
}	t_rayhit;

typedef struct s_sprite
{
	t_vec			map_pos;
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

// debug
void			debug_print_vec(t_vec *vec, char *str);
void			debug_print_player(t_player *player);
void			debug_print_ray(t_ray *ray, t_rayhit *hit);
void			debug_print_sprite(t_sprite *sprite);

// error
void			errexit_msg(char *msg);
void			errexit_mlx_errno(void);

// utils
t_hexcolor		convert_to_hexcode(unsigned char r, unsigned char g,
					unsigned char b, unsigned char a);
int				coor_to_pixel(int width, int x, int y);
double			rotate_x(double x, double y, double angle);
double			rotate_y(double x, double y, double angle);

// initialize
int				initialize_mlx_data(t_game *game);

// hook
void			hook(void *param);

// render
int				render_world(t_game *game);
void			cast_ray(t_rayhit *hit, t_game *game, t_vec ray_dir);
void			render_sprite(t_game *game, double *wall_height);

#endif
