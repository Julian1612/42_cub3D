/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sound.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorbke <lorbke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 07:08:22 by lorbke            #+#    #+#             */
/*   Updated: 2023/04/14 23:54:09 by lorbke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h" // SOUND_MAX
#include "../libraries/libft/src/libft/libft.h" // ft_strjoin
#include <fcntl.h>
#include <unistd.h>
#include <signal.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#define SOUND_FILE "sound_pid"

static int	find_sound_id(char *s, FILE *file_stream)
{
	char	*buff;
	char	*sub_str;
	int		sound_id;
	size_t	buff_size;

	buff = NULL;
	sound_id = 0;
	buff_size = 0;
	while (getline(&buff, &buff_size, file_stream) >= 0)
	{
		if (buff && ft_strnstr(buff, s, ft_strlen(buff)) != NULL)
		{
			sub_str = ft_substr(buff, 0, 10);
			sound_id = ft_atoi(sub_str);
			free(sub_str);
			free(buff);
			break ;
		}
	}
	return (sound_id);
}

int	sound_get_id(char *s)
{
	FILE	*file_stream;
	int		sound_id;
	int		sound_file_fd;
	int		temp_fd;

	temp_fd = dup(STDOUT_FILENO);
	sound_file_fd = open(SOUND_FILE, O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if (temp_fd == -1 || sound_file_fd == -1)
		return (0);
	dup2(sound_file_fd, STDOUT_FILENO);
	system("ps");
	dup2(temp_fd, STDOUT_FILENO);
	close(temp_fd);
	close(sound_file_fd);
	file_stream = fopen(SOUND_FILE, "r");
	if (file_stream == NULL)
		return (0);
	sound_id = find_sound_id(s, file_stream);
	fclose(file_stream);
	return (sound_id);
}

void	sound_stop(int sound_id)
{
	if (sound_id)
		kill(sound_id, SIGTERM);
}

void	sound_play(int *sound_id, char *path, char *cmd)
{
	if (*sound_id == 0)
		system(cmd);
	*sound_id = sound_get_id(path);
}

void	sound_stop_all(int *sound_id)
{
	int	i;

	i = 0;
	while (i < SOUND_MAX)
	{
		sound_stop(sound_id[i]);
		i++;
	}
	unlink(SOUND_FILE);
}
