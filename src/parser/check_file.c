/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jschneid <jschneid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/01 17:13:43 by jschneid          #+#    #+#             */
/*   Updated: 2023/03/10 10:06:24 by jschneid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "private_parser.h"
#include <stdio.h>

static int	check_data_type(char *path, char *data_type);

int	check_file(char *cub_file_path, char *data_type)
{
	int	fd;

	fd = open(cub_file_path, O_RDONLY);
	if (fd < 0)
	{
		error_message(2);
		return (1);
	}
	close(fd);
	if (check_data_type(cub_file_path, data_type))
	{
		error_message(3);
		return (1);
	}
	return (0);
}

static int	check_data_type(char *path, char *data_type)
{
	int	path_len;
	int	len_type;

	path_len = ft_strlen(path);
	len_type = ft_strlen(data_type);
	if (path_len >= len_type
		&& ft_strncmp(path + (path_len - len_type), data_type, len_type))
		return (1);
	return (0);
}
