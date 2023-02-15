/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jschneid <jschneid@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/01 17:13:43 by jschneid          #+#    #+#             */
/*   Updated: 2023/02/15 18:11:41 by jschneid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include <stdio.h>

static int	check_data_type(char *path, char *data_type);

int	check_file(char *str, char *data_type)
{
	int	fd;

	fd = open(str, O_RDONLY);
	close(fd);
	if (fd < 0)
	{
		error_message(2);
		return (1);
	}
	if (check_data_type(str, data_type))
	{
		error_message(3);
		return (1);
	}
	return (0);
}

static int	check_data_type(char *path, char *data_type)
{
	int	path_len;
	int	dt_len; // anderen namen wählen

	path_len = ft_strlen(path);
	dt_len = ft_strlen(data_type);
	if (path_len >= dt_len
		&& ft_strncmp(path + (path_len - dt_len), data_type, dt_len))
		return (1);
	return (0);
}
