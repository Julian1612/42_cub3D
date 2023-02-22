/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jschneid <jschneid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/11 12:26:57 by jschneid          #+#    #+#             */
/*   Updated: 2022/05/27 13:23:08 by jschneid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

void	ft_putnbr_fd(int n, int fd);

void	ft_putnbr_fd(int n, int fd)
{
	long	mod;
	long	num;

	num = n;
	if (num < 0)
	{
		write(fd, "-", 1);
		num *= -1;
	}
	mod = num % 10 + 48;
	num /= 10;
	if (num > 0)
		ft_putnbr_fd(num, fd);
	ft_putchar_fd(mod, fd);
}

int main ()
{
	int i = 234;

	ft_putnbr_fd(i, 1);
	printf("%i", i);
}
