/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jschneid <jschneid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 15:15:43 by jschneid          #+#    #+#             */
/*   Updated: 2023/03/21 18:40:59 by jschneid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "private_minimap.h"

void draw_sqr(void* param)
{
	t_game	*game;

	game = (t_game *)param;
	int j;
	int i;

	printf("gruss\n");
	i = 0;
	while (i < 10)
	{
		j = 0;
		while(j < 10)
		{
			uint32_t color = convert_to_hexcode(255, 255, 255, 255);
			mlx_put_pixel(game->minimap.test, i, j, color);
			j++;
		}
		i++;
	}
}

int	render_minimap(t_minimap *minimap_data)
{

}
