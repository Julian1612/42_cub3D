/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorbke <lorbke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 19:06:51 by lorbke            #+#    #+#             */
/*   Updated: 2023/04/14 23:27:22 by lorbke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "private_loop.h" // loop funcs
#include "../render.h" // render funcs
#include "../cub3D.h" // t_game
#include <stdbool.h> // bool

static void	handle_esc(mlx_t *mlx, int *sound_id)
{
	if (mlx_is_key_down(mlx, MLX_KEY_ESCAPE))
	{
		mlx_close_window(mlx);
		sound_stop_all(sound_id);
		errexit_msg("Escape pressed. Exiting program.");
	}
}

static void	game_loop(t_game *game, double fps_mult)
{
	loop_logic(game, fps_mult);
	loop_graphic(game);
}

static bool	has_won(t_map *map, t_player *player)
{
	if (map->arr[(int)player->pos.y][(int)player->pos.x] == EXIT)
		return (true);
	return (false);
}

static void	loop_2(t_game *game, double fps_mult)
{
	if (game->player.health <= 0)
	{
		game->img_minimap->enabled = false;
		game->hud.img->enabled = false;
		game->hud.img_str->enabled = false;
		sound_stop(game->sound_id[SOUND_GAME]);
		sound_play(&game->sound_id[SOUND_LOSE],
			"./sounds/lose.mp3", "afplay ./sounds/lose.mp3 &");
		lose_loop(&game->lose, game->mlx, game->map.textures);
	}
	else
	{
		sound_stop(game->sound_id[SOUND_START]);
		sound_play(&game->sound_id[SOUND_GAME],
			"./sounds/game.mp3", "afplay ./sounds/game.mp3 &");
		game_loop(game, fps_mult);
	}
}

void	loop(void *param)
{
	t_game	*game;
	double	fps_mult;

	game = (t_game *)param;
	fps_mult = get_fps_mult(game->mlx->delta_time, FPS);
	handle_esc(game->mlx, game->sound_id);
	if (game->start.active == true)
	{
		sound_play(&game->sound_id[SOUND_START],
			"./sounds/start.mp3", "afplay ./sounds/start.mp3 &");
		start_loop(&game->start, game->mlx, game->map.textures, game->sound_id);
	}
	else if (has_won(&game->map, &game->player) == true)
	{
		game->img_minimap->enabled = false;
		game->hud.img->enabled = false;
		game->hud.img_str->enabled = false;
		sound_stop(game->sound_id[SOUND_GAME]);
		sound_play(&game->sound_id[SOUND_WIN],
			"./sounds/win.mp3", "afplay ./sounds/win.mp3 &");
		win_loop(&game->win, game->mlx, game->map.textures);
	}
	else
		loop_2(game, fps_mult);
}
