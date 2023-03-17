#include <stdio.h>
#include <math.h>

double	get_y_from_x(double x, double ray_dir)
{
	double	opposite;

	opposite = x * tan(ray_dir) * -1;
	return (opposite);
}

double	get_x_from_y(double y, double ray_dir)
{
	double	opposite;

	y *= -1;
	opposite = y / tan(ray_dir);
	return (opposite);
}

int	main(void)
{
	double	res;

	// res = get_y_from_x(0.707, 7 * M_PI / 4);
	res = get_x_from_y(0.707, 5 * M_PI / 4);
	printf("res: %f\n", res);
	return (0);
}
