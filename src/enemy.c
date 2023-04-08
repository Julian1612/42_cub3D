
#include "cub3D.h" // t_game
#include "../libraries/mlx/include/MLX42/MLX42.h" // MLX_functions
#include <math.h> // cos, sin
#include <stdbool.h> // bool

#define ENEMY_SPEED 0.005

static void	move(t_vec *pos, t_map *map, double x_offset, double y_offset, int enemy_num)
{
	if (!check_collision(pos->x + x_offset, pos->y, map, enemy_num))
		pos->x += x_offset;
	if (!check_collision(pos->x, pos->y + y_offset, map, enemy_num))
		pos->y += y_offset;
}

static void	attack(t_player *player, t_enemy *enemy)
{
	static int	cooldown = 0;

	if (cooldown == 0)
	{
		cooldown = mlx_get_time();
		player->health -= enemy->damage;
	}
	else if (mlx_get_time() - cooldown > 1)
	{
		cooldown = mlx_get_time();
		player->health -= enemy->damage;
	}
}

void	enemies(t_enemy *enemies, t_map *map, t_player *player)
{
	t_vec	dir;
	double	angle;
	int		i;

	i = 0;
	while (i < map->enemy_count)
	{
		angle = atan2(player->pos.y - enemies[i].pos.y, player->pos.x - enemies[i].pos.x);
		dir.x = cos(angle);
		dir.y = sin(angle);
		enemies[i].tex = &map->textures[ZOMBIE_RUN1 + get_frame()];
		if (fabs(enemies[i].pos.x - player->pos.x) < 0.5 && fabs(enemies[i].pos.y - player->pos.y) < 0.5)
			attack(player, &enemies[i]);
		else
			move(&enemies[i].pos, map, dir.x * ENEMY_SPEED, dir.y * ENEMY_SPEED, i);
		i++;
	}
}
