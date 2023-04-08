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

# ifndef DEBUG
#  define DEBUG 0
# endif

# define WIDTH 400
# define HEIGHT 400
# define ERROR -1
# define SUCCESS 0
# define MM_BLOCK_SIZE 64
# define WALL '1'
# define FPS 60
# define MODE_WALL 0
# define MODE_ENEMY 1

/* ************************************************************************** */
/* ENUMS																	  */
/* ************************************************************************** */

enum e_tex_id
{
	NORTH,
	EAST,
	SOUTH,
	WEST,
	KNIGHT,
	LAMP,
	TABLE,
	GUN1,
	GUN2,
	GUN3,
	GUN4,
	GUN5,
	GUN6,
	ZOMBIE_RUN1,
	ZOMBIE_RUN2,
	ZOMBIE_RUN3,
	ZOMBIE_LEFT1,
	ZOMBIE_LEFT2,
	ZOMBIE_LEFT3,
	ZOMBIE_RIGHT1,
	ZOMBIE_RIGHT2,
	ZOMBIE_RIGHT3,
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

// @todo switch tex for pixels
typedef struct s_texture
{
	char			*path;
	mlx_texture_t	*tex;
}	t_tex;

typedef struct s_object
{
	t_vec			pos;
	t_tex			*tex;
	enum e_obj_type
	{
		DECOR_NON_PERM,
		DECOR_PERM,
		WEAPON,
		COIN,
		ENEMY,
	}	type;
}	t_object;

// @note ammunition is not implemented
typedef struct s_weapon
{
	t_tex			*tex;
	char			damage;
	char			range;
	char			reload_time;
}	t_weapon;

// @note enemies are always oriented towards the player
// @todo speed is not used
typedef struct s_enemy
{
	t_vec			pos;
	t_tex			*tex;
	char			health;
	double			speed;
	int				damage;
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
	char		**arr;
	t_tex		*textures;
	t_object	*objects;
	int			obj_count;
	t_enemy		*enemies;
	int			enemy_count;
	t_hexcolor	ceiling_color;
	t_hexcolor	floor_color;
}	t_map;

// @note weapon is pointer because the player can change weapons
typedef struct s_player
{
	t_vec			pos;
	t_vec			cplane;
	t_vec			dir;
	int				health;
	t_weapon		*weapon;
}	t_player;

// @note items might be added here
typedef struct s_game
{
	mlx_t			*mlx;
	mlx_image_t		*img_world;
	mlx_image_t		*img_hud;
	t_map			map;
	t_minimap		minimap;
	t_player		player;
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
	int				enemy_index;
	enum e_tex_id	tex_id;
}	t_rayhit;

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

// collision
bool			check_collision(double x, double y, t_map *map, int enemy_num);
int				check_enemy_collision(double x, double y, t_map *map, int enemy_num);

// render
void			render_all(t_game *game);
void			cast_ray(t_rayhit *hit, t_game *game, t_vec ray_dir, bool mode);
void			render_sprites(t_game *game, t_object *objects, t_enemy *enemies, double *wall_height);

// frame
bool			skip_frame(mlx_t *mlx, int fps);
int				get_frame(void);
bool			is_cooldown(void);

// enemy
void			enemies(t_enemy *enemies, t_map *map, t_player *player);

#endif
