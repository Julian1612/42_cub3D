
#include "../libraries/mlx/include/MLX42/MLX42.h" // MLX_functions
#include <stdbool.h> // bool

bool	is_cooldown(void)
{
	static int	cooldown = 0;

	if (cooldown == 0)
		cooldown = mlx_get_time();
	if (mlx_get_time() - cooldown > 0.2)
	{
		cooldown = mlx_get_time();
		return (false);
	}
	return (true);
}

bool	is_next_frame(double *last_frame_time)
{
	if (mlx_get_time() - *last_frame_time > 0.125)
	{
		*last_frame_time = mlx_get_time();
		return (true);
	}
	return (false);
}

double	get_fps_mult(double delta_time, int fps)
{
	return (delta_time * fps);
}
