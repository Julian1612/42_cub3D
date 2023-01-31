/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jschneid <jschneid@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 19:14:00 by jschneid          #+#    #+#             */
/*   Updated: 2023/01/31 14:55:06 by jschneid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include <stdio.h>

int parser(int *argc, char **argv)
{
	(void)argv;
	(void)argc;
	if (*argc > 2 || *argc < 2)
	{
		printf("error");
		return (0);
	}
	else
		printf("correct");
	return (0);
}
