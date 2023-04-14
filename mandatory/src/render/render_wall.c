/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_wall.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorbke <lorbke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 14:22:53 by lorbke            #+#    #+#             */
/*   Updated: 2023/04/15 00:52:51 by lorbke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "private_render.h" // render funcs
#include "../raycast.h" // t_rayhit
#include "../../libraries/mlx42/include/MLX42/MLX42.h" // mlx typedefs

static void	draw_wall(mlx_image_t *img,
	mlx_texture_t *tex, double tex_offset, t_coor *fcknorm)
{
	t_coor		tex_coor;
	int			temp;
	t_coor		img_coor;
	double		ratio;
	int			img_y_wall_end;

	tex_coor.x = tex->width * tex_offset;
	temp = 0;
	img_coor.x = fcknorm->x;
	img_coor.y = img->height / 2 - fcknorm->y / 2;
	if (img_coor.y < 0)
	{
		temp = -img_coor.y;
		img_coor.y = 0;
	}
	ratio = (double)tex->height / fcknorm->y;
	img_y_wall_end = img->height / 2 + fcknorm->y / 2;
	while ((uint32_t)img_coor.y < img->height && img_coor.y < img_y_wall_end)
	{
		tex_coor.y = temp * ratio;
		tex_pixel_to_img(img, tex, &tex_coor, &img_coor);
		temp++;
		img_coor.y++;
	}
}

static void	draw_ceiling(
	mlx_image_t *img, int wall_height, int img_x, t_hexcolor color)
{
	int			ceil_height;
	uint32_t	img_y;

	ceil_height = img->height / 2 - wall_height / 2;
	if (ceil_height < 0)
		ceil_height = 0;
	img_y = 0;
	while (img_y < img->height && img_y < (uint32_t)ceil_height)
	{
		mlx_put_pixel(img, img_x, img_y, color);
		img_y++;
	}
}

static void	draw_floor(
	mlx_image_t *img, int wall_height, int img_x, t_hexcolor color)
{
	int			floor_start;
	uint32_t	img_y;

	floor_start = img->height / 2 + wall_height / 2;
	img_y = floor_start;
	while (img_y < img->height && img_y < img->height)
	{
		mlx_put_pixel(img, img_x, img_y, color);
		img_y++;
	}
}

static void	set_ray_dir(
	t_vec *ray_dir, double x, int img_width, t_player *player)
{
	double	camera_x;

	camera_x = 2 * x / img_width - 1;
	ray_dir->x = player->dir.x + player->cplane.x * camera_x;
	ray_dir->y = player->dir.y + player->cplane.y * camera_x;
}

void	walls_render(t_game *game, int *wall_height)
{
	t_rayhit	ray_hit;
	t_vec		ray_dir;
	t_coor		fcknorm;
	uint32_t	img_x;

	img_x = 0;
	while (img_x < game->img_world->width)
	{
		set_ray_dir(&ray_dir, img_x, game->img_world->width, &game->player);
		raycast_cast_ray(&ray_hit, game, ray_dir);
		wall_height[img_x] = game->img_world->height / ray_hit.dist;
		draw_ceiling(game->img_world, wall_height[img_x],
			img_x, game->map.ceiling_color);
		fcknorm.x = img_x;
		fcknorm.y = wall_height[img_x];
		draw_wall(game->img_world, game->map.textures[ray_hit.tex_id].tex,
			ray_hit.x_offset, &fcknorm);
		draw_floor(game->img_world, wall_height[img_x],
			img_x, game->map.floor_color);
		img_x++;
	}
}
