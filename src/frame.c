
#include "../libraries/mlx/include/MLX42/MLX42.h" // MLX_functions
#include <stdbool.h> // bool

bool	skip_frame(mlx_t *mlx, int fps)
{
	if (mlx->delta_time * fps > 1.1)
		return (true);
	return (false);
}
