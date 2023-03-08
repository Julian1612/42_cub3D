/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_map.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jschneid <jschneid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 14:08:23 by jschneid          #+#    #+#             */
/*   Updated: 2023/03/08 14:14:54 by jschneid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "private_get_map.h"
#include <stdio.h>

static int	finde_map_in_file(char **raw_map, int *i);
static int	check_for_texture(char **raw_map, int *i, int j, int *flage);
static int	validate_map_position(char **raw_map, int i, int j, int flage);
static int	remove_newline_from_arr(char **raw_map, int i);

int	get_map(t_map *map_data, char *cub_file_path)
{
	int	fd;
	int	file_len;
	char *line;

	line = NULL;
	fd = open(cub_file_path, O_RDONLY);
	file_len = get_file_len(cub_file_path);
	if (finde_map_in_file(fd, line))
		return (1);
	printf("line = %s\n", line);
	// if (remove_newline_from_arr(raw_map, start_map))
	// 	return (1);
	// if (put_map_in_arr(raw_map, map_data, start_map))
	// 	return (1);
	// if (check_map(map_data->map))
	// 	return (1);
	return (0);
}

static int	finde_map_in_file(char *cub_file_path)
{
	int		j;
	int		row_len;
	int		flage;

	j = 0;
	flage = 0;
    if (fd == -1)
	{
		error_message(2);
		return (1);
	}
	while (raw_map[*i] != NULL)
	{
		row_len = ft_strlen(raw_map[*i]);
		while (j < row_len)
		{
			if (check_for_texture(raw_map, i, j, &flage))
				break ;
			if (validate_map_position(raw_map, *i, j, flage))
				return (1);
			else if (raw_map[*i][j] == '1')
				return (0);
			j++;
		}
		j = 0;
		(*i)++;
	}
	error_get_map(9);
	return (1);
}

static int	check_for_texture(char **raw_map, int *i, int j, int *flage)
{
	if (raw_map[*i][j] == 'S' || raw_map[*i][j] == 'N'
		|| raw_map[*i][j] == 'W' || raw_map[*i][j] == 'E'
		|| raw_map[*i][j] == 'C' || raw_map[*i][j] == 'F')
	{
		(*flage)++;
		return (1);
	}
	return (0);
}

static int	validate_map_position(char **raw_map, int i, int j, int flage)
{
	if (flage < 6 && raw_map[i][j] == '1')
	{
		ft_free_arr(raw_map);
		error_get_map(13);
		return (1);
	}
	return (0);
}
// @todo kann ich den shit einfach null terminiueren oder muss da was anderes gemadhrt weren

int static	remove_newline_from_arr(char **raw_map, int i)
{
	int		j;

	while (raw_map[i] != NULL)
	{
		j = 0;
		if (raw_map[i][0] == '\n')
		{
			error_get_map(15);
			ft_free_arr(raw_map);
			return (1);
		}
		while (raw_map[i][j] != '\0')
		{
			if (raw_map[i][j] == '\n')
				raw_map[i][j] = '\0';
			j++;
		}
		i++;
	}
	return (0);
}
