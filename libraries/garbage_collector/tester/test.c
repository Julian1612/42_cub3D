
#include <stdio.h>
#include "waste_wizard.h"

int	main(void)
{
	char	*str;

	ww_add_area(0);
	str = ww_malloc_and_add(0, 1, 100);
	str = ww_malloc_and_add(0, 1, 100);
	str = ww_malloc_and_add(0, 1, 100);
	ww_add_area(1);
	str = ww_malloc_and_add(1, 1, 100);
	str = ww_malloc_and_add(0, 1, 100);
	ww_free_all_areas();
	printf("1\n");
	return (0);
}
