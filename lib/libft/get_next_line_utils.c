/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jschneid <jschneid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 09:37:49 by jschneid          #+#    #+#             */
/*   Updated: 2022/08/17 15:23:57 by jschneid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*gnl_strchr(char const *s, int c)
{
	int	i;

	i = 0;
	if (!s)
		return (NULL);
	while (s[i] != '\0')
	{
		if ((unsigned char) s[i] == (unsigned char)c)
			return ((char *) s + i);
		i++;
	}
	if (c == '\0')
		return ((char *) s + i);
	return ((char *) NULL);
}

char	*gnl_strjoin(char *s1, char *s2)
{
	char	*str;
	int		i;
	int		j;

	if (!s1)
	{
		s1 = (char *)malloc(sizeof(char));
		if (!s1)
			return (NULL);
		s1[0] = 0;
	}
	str = malloc((ft_strlen(s1) + gnl_strlen(s2)) * sizeof(char) + 1);
	if (!str)
		return (NULL);
	i = 0;
	while (s1[i++] != '\0')
		str[i - 1] = s1[i - 1];
	j = 0;
	while (s2[j++] != '\0')
		str[j - 1 + i - 1] = s2[j - 1];
	str[j - 1 + i - 1] = '\0';
	free(s1);
	return (str);
}

char	*gnl_substr(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	size_t	new_len;
	char	*str;

	if (!s)
		return (NULL);
	if (gnl_strlen(s) < start)
		return (ft_strdup(""));
	new_len = gnl_strlen(s + start);
	if (new_len < len)
		len = new_len;
	str = (char *)malloc((len + 1) * sizeof(char));
	if (str == NULL)
		return (NULL);
	i = 0;
	while (i < len)
	{
		str[i] = s[i + start];
		i++;
	}
	str[i] = '\0';
	return (str);
}

char	*gnl_strdup(const char *s1)
{
	int		len;
	void	*str;

	if (!s1)
		return (NULL);
	len = gnl_strlen(s1) + 1;
	str = malloc(len * sizeof(char));
	if (str == NULL)
		return (NULL);
	gnl_strlcpy(str, s1, len);
	return (str);
}

size_t	gnl_strlcpy(char *dst, const char *src, size_t destsize)
{
	size_t	i;
	size_t	c;

	if (!dst || !src)
		return (0);
	i = 0;
	c = 0;
	while (src[c] != '\0')
		c++;
	if (destsize > 1)
	{
		while (i < destsize - 1 && src[i] != '\0')
		{
			dst[i] = src[i];
			i++;
		}
	}
	if (i < destsize)
		dst[i] = '\0';
	return (c);
}
