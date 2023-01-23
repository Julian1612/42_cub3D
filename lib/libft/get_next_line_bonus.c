/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jschneid <jschneid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/22 10:01:21 by jschneid          #+#    #+#             */
/*   Updated: 2022/08/17 15:20:22 by jschneid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// Reads the line from a file and returns the line
char	*get_next_line(int fd)
{
	static char	*buffer[1024];
	char		*line;

	if (BUFFER_SIZE <= 0 || fd < 0 || fd > 1024)
		return (NULL);
	buffer[fd] = get_buffer(buffer[fd], fd);
	if (!buffer[fd] || !*(buffer[fd]))
	{
		if (buffer[fd])
			free(buffer[fd]);
		buffer[fd] = NULL;
		return (NULL);
	}
	buffer[fd] = cut_buffer(buffer[fd], &line);
	if (!buffer[fd])
		return (NULL);
	return (line);
}

// Reads the line in the buffer and returns the created string.
char	*get_buffer(char *buffer, int fd)
{
	char	*cache;
	int		read_return;

	if (gnl_strchr(buffer, '\n'))
		return (buffer);
	cache = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!cache)
		return (NULL);
	read_return = 1;
	while (!gnl_strchr(buffer, '\n') && read_return > 0)
	{
		read_return = read(fd, cache, BUFFER_SIZE);
		if (read_return == -1)
			free(cache);
		if (read_return == -1)
			return (NULL);
		cache[read_return] = '\0';
		buffer = gnl_strjoin(buffer, cache);
	}
	free(cache);
	return (buffer);
}

// Cuts the line out of the buffer and
// modifies the buffer for the next function call
char	*cut_buffer(char *buffer, char **line)
{
	int		line_length;
	int		new_buffer_length;
	char	*new_buffer;

	line_length = 0;
	new_buffer_length = 0;
	while (buffer[line_length] != '\n' && buffer[line_length] != '\0')
		line_length++;
	while (buffer[line_length + new_buffer_length] != '\0')
		new_buffer_length++;
	*line = gnl_substr(buffer, 0, line_length + 1);
	if (!*line)
		free(buffer);
	if (!*line)
		return (NULL);
	new_buffer = gnl_substr(buffer, line_length + 1, new_buffer_length);
	if (!new_buffer && *line)
		free (*line);
	free(buffer);
	return (new_buffer);
}
