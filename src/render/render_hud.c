/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_hud.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jschneid <jschneid@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 14:26:54 by lorbke            #+#    #+#             */
/*   Updated: 2023/04/14 11:17:27 by jschneid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../render.h" // render funcs
#include "../../libraries/mlx/include/MLX42/MLX42.h" // mlx typedefs
#include "../../libraries/libft/src/libft/libft.h" // ft_itoa
#include <string.h> // NULL

static void	draw_damage(mlx_image_t *img, int player_health)
{
	uint32_t		i;
	uint32_t		j;
	unsigned int	alpha;
	static int		health = 0;

	if (health == 0)
		health = player_health;
	i = 0;
	while (i < img->width)
	{
		j = 0;
		while (j < img->height / 2)
		{
			alpha = 255 - j;
			if (alpha > 255 || health == player_health)
				alpha = 0;
			mlx_put_pixel(img, i, j, convert_to_hexcode(255, 0, 0, alpha));
			j++;
		}
		i++;
	}
	if (health != player_health)
		health = player_health;
}

static t_coor	handle_textures(t_game *game)
{
	t_coor				pos;
	t_tex				*weapon_tex;
	double				ratio;

	weapon_tex = &game->map.textures[game->player.weapon->frame.curr];
	if (game->player.weapon != NULL)
	{
		ratio = (double)weapon_tex->tex->height
			/ game->hud.img->height * 3;
		pos.x = game->hud.img->width / 2 - weapon_tex->tex->width / 2;
		pos.y = game->hud.img->height - weapon_tex->tex->height / ratio;
		render_texture(game->hud.img, weapon_tex, pos, ratio);
	}
	ratio = (double)game->map.textures[HUD_HEART].tex->height
		/ game->hud.img->height * 9;
	pos.x = 10;
	pos.y = game->hud.img->height
		- game->map.textures[HUD_HEART].tex->height / ratio - 10;
	render_texture(game->hud.img, &game->map.textures[HUD_HEART], pos, ratio);
	return (pos);
}

void	hud_render(t_game *game)
{
	t_coor				pos;

	pos = handle_textures(game);
	if (game->hud.img_str != NULL)
		mlx_delete_image(game->mlx, game->hud.img_str);
	game->hud.img_str = mlx_put_string(game->mlx, ft_itoa(game->player.health),
			pos.x + game->map.textures[HUD_HEART].tex->width, pos.y + 10);
	mlx_resize_image(game->hud.img_str, 100, 70);
	draw_damage(game->hud.img, game->player.health);
}
