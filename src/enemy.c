
#include "cub3D.h" // t_game
#include "../libraries/mlx/include/MLX42/MLX42.h" // MLX_functions
#include <math.h> // cos, sin
#include <stdbool.h> // bool
#include <stdio.h> // @note remove

#define ENEMY_SPEED 0.02

static void	move(t_enemy *enemy, t_map *map, double x_offset, double y_offset, int enemy_index)
{
	bool	coll_x;
	bool	coll_y;
	int		state;

	coll_x = check_collision(enemy->pos.x + x_offset, enemy->pos.y, map, enemy_index);
	coll_y = check_collision(enemy->pos.x, enemy->pos.y + y_offset, map, enemy_index);
	state = ZOMBIE_RUN1;
	if (coll_x == false && coll_y == false)
	{
		enemy->pos.x += x_offset;
		enemy->pos.y += y_offset;
	}
	else if (coll_x == false)
	{
		state = ZOMBIE_LEFT1;
		enemy->pos.x += x_offset * 2;
	}
	else if (coll_y == false)
	{
		state = ZOMBIE_RIGHT1;
		enemy->pos.y += y_offset * 2;
	}
	if (is_next_frame(&enemy->last_frame_time) == true)
	{
		enemy->curr_frame++;
		if (enemy->curr_frame > state + 2)
			enemy->curr_frame = state;
	}
}

static void	attack(t_player *player, t_enemy *enemy)
{
	static int	cooldown = 0;

	if (cooldown == 0)
	{
		cooldown = mlx_get_time();
		player->health -= enemy->damage;
		printf("player health: %d\n", player->health);
	}
	else if (mlx_get_time() - cooldown > 1)
	{
		cooldown = mlx_get_time();
		player->health -= enemy->damage;
		printf("player health: %d\n", player->health);
	}
}

static void	die(t_enemy *enemy, t_map *map, int enemy_index)
{
	if (enemy->curr_frame < ZOMBIE_DEAD1)
		enemy->curr_frame = ZOMBIE_DEAD1;
	if (is_next_frame(&enemy->last_frame_time) == true)
	{
		enemy->curr_frame++;
		if (enemy->curr_frame > ZOMBIE_DEAD8)
		{
			enemy->alive = false;
			enemy->curr_frame = ZOMBIE_DEAD1;
		}
	}
}

void	enemies(t_enemy *enemies, t_map *map, t_player *player)
{
	t_vec	dir;
	double	angle;
	int		i;

	i = -1;
	while (i++ < map->enemy_count)
	{
		if (enemies[i].alive == false)
			continue ;
		if (enemies[i].health <= 0)
		{
			die(&enemies[i], map, i);
			continue ;
		}
		angle = atan2(player->pos.y - enemies[i].pos.y, player->pos.x - enemies[i].pos.x);
		dir.x = cos(angle);
		dir.y = sin(angle);
		if (fabs(enemies[i].pos.x - player->pos.x) < 0.5 && fabs(enemies[i].pos.y - player->pos.y) < 0.5)
			attack(player, &enemies[i]);
		else
			move(&enemies[i], map, dir.x * ENEMY_SPEED, dir.y * ENEMY_SPEED, i);
	}
}
