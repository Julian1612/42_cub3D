/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_for_bonus_texture.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jschneid <jschneid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 09:59:35 by jschneid          #+#    #+#             */
/*   Updated: 2023/03/13 10:58:50 by jschneid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "private_parser.h"

static int	get_bonus_texture_file_path(t_map *map_data, char *line, int i);

int	check_for_bonus_texture(t_map *map_data, char *line)
{
	static char	*definitions[NBR_B_TEXTURES] = {DOOR, BARREL, ENEMY};
	int			i;

	i = 0;
	while (i < NBR_B_TEXTURES)
	{
		if (ft_strnstr(line, definitions[i], ft_strlen(line)) != NULL)
		{
			get_bonus_texture_file_path(map_data, line, i);
			return (1);
		}
		i++;
	}
	return (0);
}

static int	get_bonus_texture_file_path(t_map *map_data, char *line, int i)
{
	char	**splitted_str;
	char	*texture_path;

	splitted_str = ft_split(line, ' ');
	if (splitted_str == NULL)
	{
		error_message(4);
		return (1);
	}
	if (i == 0)
		cpy_line(&map_data->door, splitted_str[1], ft_strlen(splitted_str[1]));
	else if (i == 1)
		cpy_line(&map_data->barrel, splitted_str[1], ft_strlen(splitted_str[1]));
	else if (i == 2)
		cpy_line(&map_data->enemy, splitted_str[1], ft_strlen(splitted_str[1]));
	ft_free_arr(splitted_str);
	return (0);
}
