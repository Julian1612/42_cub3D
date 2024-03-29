/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   private_loop.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorbke <lorbke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 16:39:03 by lorbke            #+#    #+#             */
/*   Updated: 2023/04/14 08:41:51 by lorbke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PRIVATE_LOOP_H
# define PRIVATE_LOOP_H

/* ************************************************************************** */
/* INCLUDES																	  */
/* ************************************************************************** */

# include "../cub3D.h" // t_game

/* ************************************************************************** */
/* DEFINES																	  */
/* ************************************************************************** */

# define ENEMY_SPEED 0.04
# define MOV_SPEED 0.05
# define ROT_SPEED 0.05 

/* ************************************************************************** */
/* FUNCTIONS																  */
/* ************************************************************************** */

// loop_logic
void	loop_logic(t_game *game, double fps_mult);

// loop_graphic
void	loop_graphic(t_game *game);

// loop_logic_door
void	handle_door(t_game *game, t_player *player);

// loop_logic_keys
void	handle_action_keys(mlx_t *mlx, t_player *player, t_game *game);
void	handle_movement_keys(mlx_t *mlx, t_player *player, t_map *map);

// loop_screen
void	start_loop(t_screen *start, mlx_t *mlx, t_tex *textures, int *sound_id);
void	win_loop(t_screen *win, mlx_t *mlx, t_tex *textures);
void	lose_loop(t_screen *lose, mlx_t *mlx, t_tex *textures);

#endif
