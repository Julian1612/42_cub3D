/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_wall_horizontal.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jschneid <jschneid@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 14:12:56 by jschneid          #+#    #+#             */
/*   Updated: 2023/02/16 17:42:04 by jschneid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parser.h"
#include <stdio.h>

static int	check_from_left_to_right(char **raw_map, int *i);
static int	check_from_right_to_left(char **raw_map, int *i);

int	check_wall_horizontal(char **raw_map)
{
	int		i;

	i = 0;
	while (raw_map[i] != NULL)
	{
		if (check_from_left_to_right(raw_map, &i))
		{
			error_message(6);
			return (1);
		}
		if (check_from_right_to_left(raw_map, &i))
		{
			error_message(6);
			return (1);
		}
		i++;
	}
	return (0);
}

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
