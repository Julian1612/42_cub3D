
#ifndef PRIVATE_WASTE_WIZARD_H
# define PRIVATE_WASTE_WIZARD_H

typedef struct s_waste
{
	void			*alloc;
	void			(*func_free)(void *);
	struct s_waste	*next;
}	t_waste;

typedef struct s_area
{
	int				area_num;
	t_waste			*waste;
	struct s_area	*next;
}	t_area;


void	free_waste(int area_num);

t_area	**area_init(void);

t_waste	**waste_init(void);

#endif
