
#include "waste_wizard.h" // t_waste
#include "private_waste_wizard.h" // wizard_init
#include <stdlib.h> // NULL, malloc, free
#include <sys/errno.h> // errno
#include <unistd.h> // write

/**
 * It creates a new t_waste struct, and returns a pointer to it
 * 
 * @param alloc the pointer to the allocated memory
 * @param func_free This is the function that will be 
 * called to free the memory.
 * 
 * @return A pointer to a t_waste struct.
 */
static t_waste	*create_waste(void *alloc, void (*func_free)(void *))
{
	t_waste	*new;

	new = malloc(sizeof(t_waste));
	if (new == NULL)
	{
		ww_free_all_areas();
		exit(errno);
	}
	new->alloc = alloc;
	if (func_free == NULL)
		new->func_free = &free;
	else
		new->func_free = func_free;
	new->next = NULL;
	return (new);
}

/**
 * It frees all the waste in the waste list.
 */
void	free_waste(int area_num)
{
	t_area	*area;
	t_waste	*waste;
	t_waste	*temp;

	area = ww_get_area(area_num);
	waste = area->waste;
	while (waste != NULL)
	{
		temp = waste;
		waste = waste->next;
		temp->func_free(temp->alloc);
		free(temp);
	}
	waste = NULL;
}

/**
 * It takes a pointer to a linked list of t_waste structs, 
 * and a pointer to a t_waste struct, and
 * appends the second pointer to the end of the linked list
 * 
 * @param main The main waste list.
 * @param append the waste to be appended to the main waste
 * 
 * @return The address of the first node in the list.
 */
static t_waste	*append_waste(t_waste *main, t_waste *append)
{
	t_waste	*tmp;

	if (main == NULL)
		return (append);
	tmp = main;
	while (tmp->next != NULL)
		tmp = tmp->next;
	tmp->next = append;
	return (main);
}

/**
 * It creates a new waste and appends it to the waste list.
 * 
 * @param alloc the pointer to the allocated memory
 * @param func_free The function to call to free the memory.
 */
void	ww_add_waste(int area_num, void *alloc, void (*func_free)(void *))
{
	t_area	*area;
	t_waste	*new;
	t_waste	*waste;

	area = ww_get_area(area_num);
	if (area == NULL)
		return ;
	waste = area->waste;
	new = create_waste(alloc, func_free);
	waste = append_waste(waste, new);
}

/**
 * A wrapper for malloc that adds 
 * the allocated memory to the waste list.
 * If malloc fails, it frees all 
 * the memory in the waste list and exits.
 * 
 * @param size The size of the memory block, in bytes.
 * @param count The number of elements to allocate.
 * 
 * @return A pointer to a newly allocated memory block.
 */
void	*ww_malloc_and_add(int area_num, size_t size, size_t count)
{
	t_area	*area;
	void	*alloc;

	area = ww_get_area(area_num);
	if (area == NULL)
		return (NULL);
	alloc = malloc(size * count);
	if (alloc == NULL)
	{
		ww_free_all_areas();
		exit(errno);
	}
	ww_add_waste(area_num, alloc, free);
	return (alloc);
}
