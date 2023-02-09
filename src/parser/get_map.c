/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_map.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jschneid <jschneid@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 14:08:23 by jschneid          #+#    #+#             */
/*   Updated: 2023/02/09 18:11:44 by jschneid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include <stdio.h>

static int	finde_map_in_file(char **raw_map, int *i)
{
	int		j;
	int		row_len;

	j = 0;
	while (raw_map[*i] != NULL)
	{
		row_len = ft_strlen(raw_map[*i]);
		while (j < row_len)
		{
			if (raw_map[*i][j] == 'S' || raw_map[*i][j] == 'N'
				|| raw_map[*i][j] == 'W' || raw_map[*i][j] == 'E'
				|| raw_map[*i][j] == 'C' || raw_map[*i][j] == 'F')
				break ;
			else if (raw_map[*i][j] == '1')
				return (0);
			j++;
		}
		j = 0;
		(*i)++;
	}
	return (1);
}

// static int wall_check_vertical(char **raw_map, int i)
// {
// 	return (0);
// }

static int	check_from_right_to_left(char **raw_map, int *i)
{
	int		j;

	j = ft_strlen(raw_map[*i]) - 1;
	while (j > -1)
	{
		if (raw_map[*i][j] == '1')
		{
			while (j > -1 && raw_map[*i][j] != ' ')
				j--;
			if (raw_map[*i][j + 1] != '1')
				return (1);
		}
		j--;
	}
	return (0);
}

static int	check_from_left_to_right(char **raw_map, int *i)
{
	int		j;

	j = 0;
	while (raw_map[*i][j] != '\0')
	{
		if (raw_map[*i][j] == '1')
		{
			while (raw_map[*i][j] != '\0' && raw_map[*i][j] != ' ')
				j++;
			if (raw_map[*i][j - 1] != '1')
				return (1);
		}
		j++;
	}
	return (0);
}

// static int	check_if_wall_is_closed(char **raw_map, int *i)
// {
// 	if (check_from_left_to_right(raw_map, i))
// 		return (1);
// 	if (check_from_right_to_left(raw_map, i))
// 		return (1);
// 	return (0);
// }

static int	check_wall_horizontal(char **raw_map, int i)
{
	while (raw_map[i] != NULL)
	{
		if (check_from_left_to_right(raw_map, &i))
			return (1);
		if (check_from_right_to_left(raw_map, &i))
			return (1);
		// if (check_charackters(raw_map, &i))
		// 	return (1);
		i++;
	}
	printf("resultat: gute diese\n");
	return (0);
}

static int	check_map(char **raw_map, int i)
{
	if (check_wall_horizontal(raw_map, i))
		return (1);
	// if (wall_check_vertical(raw_map, i))
	// 	return (1);
	// if (check_map_content(raw, i))
	// 	return (1);
	return (0);
}

int static	remove_newline_from_file(char **raw_map, int i)
{
	int		j;

	while (raw_map[i] != NULL)
	{
		j = 0;
		while (raw_map[i][j] != '\0')
		{
			if (raw_map[i][j] == '\n')
				raw_map[i][j] = ' ';
			j++;
		}
		i++;
	}
	return (0);
}

int	get_map(t_map *map_data, char **raw_map)
{
	int	i;

	i = 0;
	(void)map_data;
	if (finde_map_in_file(raw_map, &i))
		return (1);
	if (remove_newline_from_file(raw_map, i))
		return (1);
	if (check_map(raw_map, i))
		return (1);
	// if (map_to_arr(raw_map, i, map_data))
	// 	return (1);
	return (0);
}
