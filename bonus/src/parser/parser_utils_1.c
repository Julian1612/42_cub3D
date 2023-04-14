/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils_1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorbke <lorbke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/09 11:28:41 by jschneid          #+#    #+#             */
/*   Updated: 2023/04/14 23:20:04 by lorbke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "private_parser.h"
#include "../../libraries/libft/src/libft/libft.h" // ft_* functions
#include "string.h" // NULL
#include <stdlib.h> // malloc, free

void	remove_last_char(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
		i++;
	str[i - 1] = '\0';
}

int	clear_mem(char **line)
{
	free(*line);
	*line = NULL;
	clear_buffer(line);
	return (1);
}

char	*ft_strjoin_free_s1(char const *s1, char const *s2)
{
	char	*str;
	int		i;
	int		j;

	if (s1 == NULL || s2 == NULL)
		return (NULL);
	str = malloc((ft_strlen(s1) + ft_strlen(s2)) * sizeof(char) + 1);
	if (str == 0)
		return (0);
	i = 0;
	while (s1[i] != '\0')
	{
		str[i] = s1[i];
		i++;
	}
	j = 0;
	while (s2[j] != '\0')
	{
		str[j + i] = s2[j];
		j++;
	}
	str[j + i] = '\0';
	free((char *)s1);
	return (str);
}

int	check_pos_in_map(t_map *map, int i, int j)
{
	if (j > 0 && map->arr[i][j - 1] == ' ')
		return (error_get_map(8, map));
	else if (map->arr[i][j + 1] == '\0'
		|| map->arr[i][j + 1] == ' ')
		return (error_get_map(8, map));
	else if (((int) ft_strlen(map->arr[i + 1]) >= j
			&& map->arr[i + 1][j] == ' ')
		|| ((int) ft_strlen(map->arr[i - 1]) >= j
			&& map->arr[i - 1][j] == ' '))
		return (error_get_map(8, map));
	else if ((int) ft_strlen(map->arr[i + 1]) <= j
		|| (int) ft_strlen(map->arr[i - 1]) <= j)
		return (error_get_map(8, map));
	return (0);
}

void	init_door(t_map *map_data, int i, int j, int count_doors)
{
	map_data->doors[count_doors].x = j;
	map_data->doors[count_doors].y = i;
	map_data->doors[count_doors].open = false;
	map_data->doors[count_doors].last_action = 0;
}
