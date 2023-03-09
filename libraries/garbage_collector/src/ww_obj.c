
#include "private_waste_wizard.h"
#include <stdlib.h> // NULL

t_area	**area_init(void)
{
	static t_area	*area = NULL;

	return (&area);
}

t_area	*ww_get_area(int area_num)
{
	t_area	*prev;
	t_area	*curr;

	prev = NULL;
	curr = *area_init();
	while (curr && curr->area_num != area_num)
	{
		prev = curr;
		curr = curr->next;
	}
	if (curr == NULL)
		return (NULL);
	return (curr);
}
