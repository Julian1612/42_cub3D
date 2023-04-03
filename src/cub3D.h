/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorbke <lorbke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 17:04:16 by jschneid          #+#    #+#             */
/*   Updated: 2023/04/02 20:05:40 by lorbke           ###   ########.fr       */
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

# define WIDTH 800
# define HEIGHT 800
# define ERROR -1
# define SUCCESS 0
# define MM_BLOCK_SIZE 64
# define WALL '1'
# define FPS 200

# ifndef DEBUG
#  define DEBUG 0
# endif

/* ************************************************************************** */
/* ENUMS																	  */
/* ************************************************************************** */

enum	e_object_id
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

typedef struct s_texture
{
	char			*path;
	mlx_texture_t	*tex;
}	t_texture;

// @note ammunition is not implemented
typedef struct s_weapon
{
	t_texture		*texture;
	char			*damage;
	char			*range;
	char			*reload_time;
}	t_weapon;

typedef struct s_minimap
{
	double			x;
	double			y;
	double			width;
	double			height;
	mlx_image_t		*player;
	mlx_image_t		*walls;
	mlx_image_t		*view_dir;
}	t_minimap;

typedef struct s_map
{
	char		**map;
	t_texture	*objects;
	t_hexcolor	ceiling_color;
	t_hexcolor	floor_color;
}	t_map;

// @note weapon is pointer because the player can change weapons
typedef struct s_player
{
	double			x;
	double			y;
	double			view_dir;
	t_weapon		*weapon;
}	t_player;

// @note enemies are always oriented towards the player
typedef struct s_enemy
{
	double			x;
	double			y;
	t_texture		*texture;
	char			health;
	char			*speed;
	t_weapon		weapon;
}	t_enemy;

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

typedef struct s_coor
{
	double	x;
	double	y;
}	t_coor;

// @todo move to raycaster header
typedef struct s_ray
{
	double	angle;
	t_coor	dir;
	t_coor	origin;
	int		map_x;
	int		map_y;
	t_coor	step;
	t_coor	hypotenuse;
	t_coor	length;
	bool	y_side;
}				t_ray;

typedef struct s_rayhit
{
	double				stripe;
	double				dist;
	enum e_object_id	wall_id;
}	t_rayhit;

typedef struct s_sprite
{
	double			x;
	double			y;
	t_texture		*texture;
}	t_sprite;

/* ************************************************************************** */
/* FUNCTIONS																  */
/* ************************************************************************** */

void			debug_print_player(t_player *player);
void			debug_print_ray(t_ray *ray, t_rayhit *hit);

void			errexit_msg(char *msg);
void			errexit_mlx_errno(void);

t_hexcolor		convert_to_hexcode(unsigned char r, unsigned char g,
					unsigned char b, unsigned char a);
int				coor_to_pixel(int width, int x, int y);

int				initialize_mlx_data(t_game *game);

void			hook(void *param);

int				render_world(t_game *game);

void			cast_ray(t_rayhit *hit, t_game *game, double ray_dir);

void			init_sprite(t_game *game);

#endif
