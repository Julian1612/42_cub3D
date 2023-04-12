/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   private_loop.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorbke <lorbke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 16:39:03 by lorbke            #+#    #+#             */
/*   Updated: 2023/04/12 20:52:13 by lorbke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PRIVATE_LOOP_H
# define PRIVATE_LOOP_H

/* ************************************************************************** */
/* INCLUDES																	  */
/* ************************************************************************** */

# include "../cub3D.h" // t_game

/* ************************************************************************** */
/* FUNCTIONS																  */
/* ************************************************************************** */

// loop_logic
void	loop_logic(t_game *game);

// loop_graphic
void	loop_graphic(t_game *game);

// loop_switch_state
void	switch_state_door(t_game *game, t_player *player);
void	switch_state_minimap(t_game *game, t_player *player);

#endif
