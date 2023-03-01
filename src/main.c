/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jschneid <jschneid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 15:28:59 by jschneid          #+#    #+#             */
/*   Updated: 2023/03/01 17:24:27 by jschneid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"
#include "parser.h"
#include "player_position.h"
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#define WIDTH 512
#define HEIGHT 512
#define PLAYER_SIZE 2
#define DIRECTION 2
#define WALL_BLOCK 64
#define NBR_OF_RAYS 1


static mlx_image_t	*img;
static mlx_image_t	*view_direction;
static mlx_image_t	*walls;
static mlx_image_t	*ray;

int draw_ray(mlx_t *mlx, t_player *player, t_map *map_data)
{
	double	player_pos_x = player->x, player_pos_y = player->y;
	double	cam_pos_horizontal;
	double	line_of_sight_x = -1, line_of_sight_y = 0;
	double	plane_x = 0, plane_y = 0.66;
	double	cameraPositionX;
	double	ray_dir_x, ray_dir_y;
	double	len_ray_x, len_ray_y;
	double	dist_x, dist_y;
	double	wall_distance; 
	int		pos_map_x, pos_map_y;
	int		step_x;
	int		step_y;
	int		wall_hit = 0;
	int		hit_side;
	int		i;
	int		rays = 2;
	int		wall_height;
	int		bottom_wall;
	int		top_wall;

	while()
	{
		while(i < rays)
		{
			//calculate ray position and direction
			// cam_pos_horizontal = 2 * i / (double)
			ray_dir_x = line_of_sight_x + plane_x * cam_pos_horizontal;
			ray_dir_y = line_of_sight_y + plane_y * cam_pos_horizontal;
			// get positon in map
			pos_map_x = (int)player_pos_x;
			pos_map_y = (int)player_pos_y;
			//length of ray from one x or y-hit_side to next x or y-hit_side
			if (ray_dir_x == 0)
			    dist_x = 1e30; // macro erstellen
			else 
    			dist_x = fabs(1 / ray_dir_x);
			if (ray_dir_y == 0) 
    			dist_y = 1e30;
			else
    			dist_y = fabs(1 / ray_dir_y);
			//calculate step and initial sideDist
			if(ray_dir_x < 0)
      		{
      		  step_x = -1;
      		  len_ray_x = (player_pos_x - pos_map_x) * dist_x;
      		}
      		else
      		{
      		  step_x = 1;
      		  len_ray_x = (pos_map_x + 1.0 - player_pos_x) * dist_x;
      		}
      		if(ray_dir_y < 0)
      		{
      		  step_y = -1;
      		  len_ray_y = (player_pos_y - pos_map_y) * dist_y;
      		}
      		else
      		{
      		  step_y = 1;
      		  len_ray_y = (pos_map_y + 1.0 - player_pos_y) * dist_y;
      		}
			//perform DDA
      		while(wall_hit == 0)
      		{
        	//jump to next map square, either in x-direction, or in y-direction
        	if(len_ray_x < len_ray_y)
        	{
        	  len_ray_x += dist_x;
        	  pos_map_x += step_x;
        	  hit_side = 0;
        	}
        	else
        	{
        	  len_ray_y += dist_y;
        	  pos_map_y += step_y;
        	  hit_side = 1;
        	}
        	//Check if ray has wall_hit a wall
        	if(map_data->map[pos_map_x][pos_map_y] == '1') 
				wall_hit = 1;
			}
			//Calculate distance projected on camera direction.
			if(hit_side == 0)
				wall_distance = (len_ray_x - dist_x);
     		else
				wall_distance = (len_ray_y - dist_y);
			//Calculate height of line to draw on screen
      		wall_height = (int)(h / wall_distance);
			//calculate lowest and highest pixel to fill in current stripe
      		bottom_wall = -wall_height / 2 + h / 2;
      		if(bottom_wall < 0) 
				bottom_wall = 0;
      		top_wall = wall_height / 2 + h / 2;
      		if(top_wall >= h)
				top_wall = h - 1;

			// make a function which gives the correct color for the wall

			// if(hit_side == 1) 
			// 	color = color / 2;

			// draw vertical line
			i++;
		}
	}
	return (0);
}

void hook(void* param)
{
	t_hook		*hook_data;
	t_player	*player;
	mlx_t		*mlx;
	t_map		*map_data;

	hook_data = param;
	mlx = hook_data->mlx;
	player = hook_data->player;
	map_data = hook_data->map_data;
	if (mlx_is_key_down(mlx, MLX_KEY_ESCAPE))
		mlx_close_window(mlx);
	if (mlx_is_key_down(mlx, MLX_KEY_W))
	{
		img->instances[0].y += cos(player->player_angle) * 5;
		img->instances[0].x += sin(player->player_angle) * 5;
	}
	if (mlx_is_key_down(mlx, MLX_KEY_S))
	{
		img->instances[0].y -= cos(player->player_angle) * 5;
		img->instances[0].x -= sin(player->player_angle) * 5;
	}
	if (mlx_is_key_down(mlx, MLX_KEY_D))
	{
		img->instances[0].y += cos(player->player_angle - M_PI_2) * 5;
		img->instances[0].x += sin(player->player_angle - M_PI_2) * 5;
	}
	if (mlx_is_key_down(mlx, MLX_KEY_A))
	{
		img->instances[0].y += cos(player->player_angle + M_PI_2) * 5;
		img->instances[0].x += sin(player->player_angle + M_PI_2) * 5;
	}
	if (mlx_is_key_down(mlx, MLX_KEY_LEFT))
		player->player_angle += M_PI / 180 * 5;
	if (mlx_is_key_down(mlx, MLX_KEY_RIGHT))
		player->player_angle -= M_PI / 180 * 5;
	if (player->player_angle > M_PI * 2)
		player->player_angle = 0;
	if (player->player_angle < M_PI * -2)
		player->player_angle = 0;
	view_direction->instances[0].y = img->instances[0].y + 10 * cos(player->player_angle);
	view_direction->instances[0].x = img->instances[0].x + 10 * sin(player->player_angle);
	printf("%f\n", player->player_angle);
	draw_ray(mlx, player, map_data);

}

int draw_walls(mlx_t *mlx, t_map *map_data)
{
	int i = 0;
	int j = 0;

	while (map_data->map[i] != NULL)
	{
		while (map_data->map[i][j] != '\0')
		{
			if (map_data->map[i][j] == '1')
				mlx_image_to_window(mlx, walls, i, j);
			j++;
		}
		j = 0;
		i++;
	}
	return 0;
}


int	main(int argc, char **argv)
{
	mlx_t			*mlx;
	t_player		player;
	t_hook			hook_data;
	t_map			map_data;
	// t_player		player_pos;
	int i = 0;
	int j = 0;

	(void)argc;
	(void)argv;
	if (parser(&argc, argv, &map_data))
		return (1);
	if (!(mlx = mlx_init ((map_data.map_hight * WALL_BLOCK),(map_data.map_width * WALL_BLOCK)-WALL_BLOCK, "Cub3D", true)))
		return (EXIT_FAILURE);
	player.player_angle = 0;
	hook_data.mlx = mlx;
	hook_data.player = &player;
	hook_data.map_data = &map_data;
	// if (init_player_position(&map_data, &player_pos))
	// 	return (1);
	img = mlx_new_image(mlx, PLAYER_SIZE, PLAYER_SIZE);
	view_direction = mlx_new_image(mlx, DIRECTION, DIRECTION);
	walls = mlx_new_image(mlx, WALL_BLOCK, WALL_BLOCK);
	ray = mlx_new_image(mlx, WALL_BLOCK, WALL_BLOCK);
	memset(img->pixels, 255, img->width * img->height * sizeof(int));
	memset(view_direction->pixels, 255, view_direction->width * view_direction->height * sizeof(int));
	memset(walls->pixels, 255, walls->width * walls->height * sizeof(int));
	memset(ray->pixels, 255, ray->width * ray->height * sizeof(int));
	while ((i * WALL_BLOCK) < (map_data.map_hight * WALL_BLOCK))
	{
		while ((j * WALL_BLOCK) < (map_data.map_width * WALL_BLOCK))
		{
			if (map_data.map[i][j] == '1')
				mlx_image_to_window(mlx, walls, i * WALL_BLOCK, j * WALL_BLOCK);
			j++;
		}
		j = 0;
		i++;
	}
	mlx_image_to_window(mlx, img, 80, 90);
	mlx_image_to_window(mlx, view_direction, 0, 0);
	mlx_image_to_window(mlx, ray, 0, 0);
	mlx_loop_hook(mlx, &hook, &hook_data);
	mlx_loop(mlx);
	mlx_terminate(mlx);
	return (0);
}
