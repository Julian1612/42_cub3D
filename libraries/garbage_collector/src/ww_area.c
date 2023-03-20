
#include "waste_wizard.h" // ww_area functions
#include "private_waste_wizard.h" // t_area, t_waste
#include <stdlib.h> // NULL, malloc, free
#include <sys/errno.h> // errno

static t_area	*create_area(int area_num)
{
	t_area	*new;

	new = malloc(sizeof(t_area));
	if (new == NULL)
	{
		ww_free_all_areas();
		exit(errno);
	}
	new->area_num = area_num;
	new->waste = NULL;
	new->next = NULL;
	return (new);
}

static t_area	*append_area(t_area *main, t_area *append)
{
	t_area	*temp;

	if (main == NULL)
		return (append);
	temp = main;
	while (temp->next != NULL)
		temp = temp->next;
	temp->next = append;
	return (main);
}

void	ww_free_all_areas(void)
{
	t_area	*area;
	t_area	*temp;
	int		area_num;

	area = *area_init();
	area_num = 0;
	while (area != NULL)
	{
		temp = area;
		area = area->next;
		free_waste(area_num);
		free(temp);
		area_num++;
	}
	*area_init() = NULL;
}

void	ww_free_area(int area_num)
{
	t_area	*area;
	t_area	*temp;
	int		i;

	area = ww_get_area(0);
	i = 0;
	while (area != NULL)
	{
		temp = area;
		area = area->next;
		free_waste(i);
		free(temp);
		i++;
	}
	if (area)
		area->waste = NULL;
}

void	ww_add_area(int area_num)
{
	t_area	*new;
	t_area	**area;

	area = area_init();
	new = create_area(area_num);
	*area = append_area(*area, new);
}
