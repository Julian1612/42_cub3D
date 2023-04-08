
#include "../libraries/mlx/include/MLX42/MLX42.h" // MLX_functions
#include <stdbool.h> // bool

bool	is_cooldown(void)
{
	static int	cooldown = 0;

	if (cooldown == 0)
		cooldown = mlx_get_time();
	if (mlx_get_time() - cooldown > 0.5)
	{
		cooldown = mlx_get_time();
		return (false);
	}
	return (true);
}

int	get_frame(void)
{
	static int	delta_time = 0;

	if (delta_time == 0)
		delta_time = mlx_get_time();
	if (mlx_get_time() - delta_time > 1)
	{
		delta_time = mlx_get_time();
		return (2);
	}
	if (mlx_get_time() - delta_time > 0.5)
		return (1);
	return (0);
}

bool	skip_frame(mlx_t *mlx, int fps)
{
	if (mlx->delta_time * fps > 1.1)
		return (true);
	return (false);
}
