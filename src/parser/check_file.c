/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jschneid <jschneid@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/01 17:13:43 by jschneid          #+#    #+#             */
/*   Updated: 2023/02/01 21:01:13 by jschneid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static int	check_data_type(char *path);

int	check_file(char **argv)
{
	int	fd;

	fd = open(argv[1], O_RDONLY);
	close(fd);
	if (fd < 0)
	{
		error_message(2);
		return (1);
	}
	if (check_data_type(argv[1]))
	{
		error_message(3);
		return (1);
	}
	return (0);
}

static int	check_data_type(char *path)
{
	int	path_len;

	path_len = ft_strlen(path);
	if (path[path_len - 3] != 'c' || path[path_len - 2] != 'u'
		|| path[path_len - 1] != 'b')
		return (1);
	return (0);
}
