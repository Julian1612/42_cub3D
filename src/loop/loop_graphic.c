/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop_graphic.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorbke <lorbke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 16:21:07 by lorbke            #+#    #+#             */
/*   Updated: 2023/04/14 06:43:37 by lorbke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../render.h" // render_all
#include "../cub3D.h" // t_game

#define ERR_WIN "Window height to width ratio \
cannot be smaller than 1 or greater than 2."

static void	resize_camera(t_player *player, int width, int height)
{
	player->cplane.x = 0;
	player->cplane.y = (double)width / height / 2;
	player->dir.x = -1;
	player->dir.y = 0;
}

static void	resize(t_game *game)
{
	static int	last_width = WIDTH;
	static int	last_height = HEIGHT;

	if (last_width == game->mlx->width && last_height == game->mlx->height)
		return ;
	if ((double)game->mlx->width / game->mlx->height < 1
		|| (double)game->mlx->width / game->mlx->height > 2)
	{
		errexit_msg(ERR_WIN);
		return ;
	}
	last_width = game->mlx->width;
	last_height = game->mlx->height;
	mlx_resize_image(game->img_world, game->mlx->width, game->mlx->height);
	mlx_resize_image(game->hud.img, game->mlx->width, game->mlx->height);
	resize_camera(&game->player, game->mlx->width, game->mlx->height);
}

void	loop_graphic(t_game *game)
{
	render_game(game);
	resize(game);
}
