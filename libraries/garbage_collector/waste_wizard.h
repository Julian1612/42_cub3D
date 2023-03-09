
#ifndef WASTE_WIZARD_H
# define WASTE_WIZARD_H

# include "src/private_waste_wizard.h" // t_waste, t_area
# include <sys/types.h> // size_t

/*********************************/
/*			DESCRIPTION			 */
/*********************************/
/* 
* This set of functions will keep track of memory allocations which can
* be added as pointers. The allocations can then later be freed.
*/

// waste
t_waste		*ww_get_waste(int area_num);
void		ww_add_waste(int area_num, void *alloc, void (*func_free)(void *));
void		*ww_malloc_and_add(int area_num, size_t size, size_t count);

// area
void		ww_free_area(int area_num);
void		ww_free_all_areas(void);
t_area		*ww_get_area(int area_num);
void		ww_add_area(int area_num);

// useful free functions
void		ww_free_str_arr(void *str_arr_void);

#endif
