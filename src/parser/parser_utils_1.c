/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils_1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jschneid <jschneid@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/09 11:28:41 by jschneid          #+#    #+#             */
/*   Updated: 2023/04/09 11:29:06 by jschneid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "private_parser.h"
#include "string.h" // NULL
#include <stdio.h>

int	clear_mem(char **line)
{
	free(*line);
	*line = NULL;
	clear_buffer(line);
	return (1);
}
