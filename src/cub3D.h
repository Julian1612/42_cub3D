/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorbke <lorbke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 17:04:16 by jschneid          #+#    #+#             */
/*   Updated: 2023/04/12 15:19:48 by lorbke           ###   ########.fr       */
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

# define WIDTH 800
# define HEIGHT 800
# define NOT_SET -1
# define ERROR -1
# define SUCCESS 0
# define MM_BLOCK_SIZE 64
# define FLOOR '0'
# define WALL '1'
# define DOOR_CLOSED 'D'
# define DOOR_OPEN 'd'
# define ENEMY 'E'
# define FPS 60

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
	DOOR_FRONT,
	DOOR_SIDE,
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
	ZOMBIE_DEAD1,
	ZOMBIE_DEAD2,
	ZOMBIE_DEAD3,
	ZOMBIE_DEAD4,
	ZOMBIE_DEAD5,
	ZOMBIE_DEAD6,
	ZOMBIE_DEAD7,
	ZOMBIE_DEAD8,
};

/* ************************************************************************** */
/* TYPEDEFS																	  */
/* ************************************************************************** */

typedef uint32_t	t_hexcolor;
typedef uint8_t		t_subpxl;

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

typedef struct s_door
{
	bool			open;
	double			last_action;
	int				x;
	int				y;
}	t_door;

typedef struct s_object
{
	t_vec			pos;
	t_tex			*tex;
	enum	e_obj_type
	{
		DECOR_NON_PERM,
		DECOR_PERM,
		WEAPON,
		COIN,
	}				type;
}	t_object;

// @note ammunition is not implemented
typedef struct s_weapon
{
	char			damage;
	char			range;
	char			reload_time;
	double			last_frame_time;
	enum e_tex_id	curr_frame;
}	t_weapon;

// @note enemies are always oriented towards the player
// @todo speed is not used
typedef struct s_enemy
{
	bool			alive;
	t_vec			pos;
	char			health;
	double			speed;
	char			damage;
	double			last_frame_time;
	enum e_tex_id	curr_frame;
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
	t_door		*doors;
	int			door_count;
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

/* ************************************************************************** */
/* FUNCTIONS																  */
/* ************************************************************************** */

// error
void			errexit_msg(char *msg);
void			errexit_mlx_errno(void);

// utils
t_hexcolor		convert_to_hexcode(unsigned char r, unsigned char g,
					unsigned char b, unsigned char a);
int				coor_to_pixel(int width, int x, int y);
double			rotate_x(double x, double y, double angle);
double			rotate_y(double x, double y, double angle);
int				ft_abs(int n);
bool			switch_bool(bool b);
double 			get_dist_of_vecs(t_vec *a, t_vec *b);

// initialize
int				initialize_mlx_data(t_game *game);

// hook
void			hook(void *param);

// collision
bool			collision_is_true(double x, double y, t_map *map, int enemy_num);
int				collision_is_enemy(double x, double y, t_map *map, int enemy_num);

// frame
double			get_fps_mult(double delta_time, int fps);
bool			is_next_frame(double *delta_time);
bool			is_cooldown(void);

// enemy
void			enemies(t_enemy *enemies, t_map *map, t_player *player, double fps_mult);

#endif
