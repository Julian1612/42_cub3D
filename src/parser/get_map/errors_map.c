/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jschneid <jschneid@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 16:45:38 by jschneid          #+#    #+#             */
/*   Updated: 2023/02/22 14:20:08 by jschneid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "private_get_map.h"
#include <stdio.h>

void	error_get_map(int error_code)
{
	if (error_code == 1)
		printf("Error!\nWrong amount of argument\n");
	else if (error_code == 4)
		printf("Error!\nMalloc failed\n");
	else if (error_code == 6)
		printf("Error!\nMap is not surrunded by walls\n");
	else if (error_code == 9)
		printf("Error!\nfile contains no map\n");
	else if (error_code == 13)
		printf("Error!\nMap is in incorrect position. Please place the\
			map under the texture declarations\n");
	else if (error_code == 15)
		printf("Error!\nEmty line in map\n");
	else if (error_code == 16)
		printf("Error!\nInvalid character in map\n");
}
