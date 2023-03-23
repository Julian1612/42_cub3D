/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorbke <lorbke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 17:04:16 by jschneid          #+#    #+#             */
/*   Updated: 2023/03/22 19:09:10 by lorbke           ###   ########.fr       */
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

# define WIDTH 1280
# define HEIGHT 800
# define ERROR -1
# define SUCCESS 0
# define MM_BLOCK_SIZE 64
# define WALL '1'

# ifndef DEBUG
#  define DEBUG 0
# endif

/* ************************************************************************** */
/* TYPEDEFS																	  */
/* ************************************************************************** */

typedef unsigned int	t_hexcolor;

typedef struct s_texture
{
	char			*path;
	xpm_t			*xpm;
	mlx_texture_t	*texture;
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
	int			width;
	int			height;
	t_texture	west;
	t_texture	east;
	t_texture	south;
	t_texture	north;
	t_texture	*sprites;
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

// @note move this?
typedef struct s_ray
{
	t_coor	dir;
	t_coor	origin;
	int		map_x;
	int		map_y;
	t_coor	step;
	t_coor	hypotenuse;
	t_coor	length;
}				t_ray;

/* ************************************************************************** */
/* FUNCTIONS																  */
/* ************************************************************************** */

void	debug_print_player(t_player *player);

void	errexit_msg(char *msg);
void	errexit_mlx_errno(void);

int		initialize_mlx_all(t_game *game);

int		render_minimap(t_minimap *minimap, mlx_t *mlx, t_map *map);
int		render_world(t_game *game);

void	hook(void *param);

double	cast_ray(t_game *game, double ray_angle);

void	debug_print_ray(t_ray *ray);

unsigned int	convert_to_hexcode(
	unsigned char r, unsigned char g, unsigned char b, unsigned char a);

#endif
