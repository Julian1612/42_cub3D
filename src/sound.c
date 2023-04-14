/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sound.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorbke <lorbke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 07:08:22 by lorbke            #+#    #+#             */
/*   Updated: 2023/04/14 08:33:57 by lorbke           ###   ########.fr       */
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

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*substr;

	if (s == NULL)
		return (NULL);
	if (start >= strlen((char *)s))
		return (calloc(1, sizeof(char)));
	if (len > strlen((char *)s))
		len = strlen((char *)s);
	substr = malloc(sizeof(char) * (len + 1));
	if (!substr)
		return (NULL);
	strlcpy(substr, s + start, len + 1);
	return (substr);
}

int	sound_get_id(char *s)
{
	FILE	*fn;
	int		sound_id;
	size_t	n;
	int		ps_fd;
	char	*buff;
	int		tmp_fd;

	tmp_fd = dup(STDOUT_FILENO);
	sound_id = 0;
	buff = NULL;
	ps_fd = open("ps", O_WRONLY | O_CREAT | O_TRUNC, 0777);
	dup2(ps_fd, STDOUT_FILENO);
	system("ps");
	dup2(tmp_fd, STDOUT_FILENO);
	close(tmp_fd);
	close(ps_fd);
	n = 0;
	fn = fopen("ps", "r");
	while (getline(&buff, &n, fn) >= 0)
	{
		if (buff && strnstr(buff, s, strlen(buff)) != NULL)
		{
			char *sub_str = ft_substr(buff, 0, 10);
			sound_id = atoi(sub_str);
			free(sub_str);
			free(buff);
			break ;
		}
	}
	if (sound_id == 0)
		free(buff);
	fclose(fn);
	return (sound_id);
}

static void	sound_start(int sound_id, char *cmd)
{
	if (sound_id == 0)
		system(cmd);
}

void	sound_stop(int sound_id)
{
	if (sound_id)
		kill(sound_id, SIGTERM);
}

void	sound_play(int *sound_id, char *path, char *cmd)
{
	sound_start(*sound_id, cmd);
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
}

// int	main(void)
// {
// 	int	pid[3];

// 	// sleep(5);
// 	// sound_stop(pid[0]);
// 	printf("pid = %d\n", pid[0]);
// 	sound_start(pid[0], "afplay ./sounds/erika.mp3 &");
// 	pid[0] = mlx_get_pid("./sounds/erika.mp3");
// 	printf("pid = %d\n", pid[0]);
// 	sleep(5);
// 	sound_stop(pid[0]);
// }
