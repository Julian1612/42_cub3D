/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errexit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorbke <lorbke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 19:07:53 by lorbke            #+#    #+#             */
/*   Updated: 2023/04/15 00:40:41 by lorbke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libraries/libft/src/libft/libft.h" // ft_putstr_fd
#include "../libraries/mlx42/include/MLX42/MLX42.h" // mlx_errno, mlx_strerror
#include <unistd.h> // file descriptor defines, exit

void	errexit_msg(char *msg)
{
	ft_putstr_fd(msg, STDERR_FILENO);
	ft_putchar_fd('\n', STDERR_FILENO);
	exit(EXIT_FAILURE);
}

void	errexit_mlx_errno(void)
{
	ft_putstr_fd("Error: ", STDERR_FILENO);
	ft_putstr_fd(mlx_strerror(mlx_errno), STDERR_FILENO);
	ft_putchar_fd('\n', STDERR_FILENO);
	exit(EXIT_FAILURE);
}
