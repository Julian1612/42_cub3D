/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jschneid <jschneid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/08 08:44:49 by jschneid          #+#    #+#             */
/*   Updated: 2022/08/11 11:45:00 by jschneid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_strtrim(char const *s1, char const *set);
static int	offset_str(char const *s1, char const *set);
static int	set_comp(char const *s1, char const *set, int i);
static int	end_str(char const *s1, char const *set);

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*str;
	int		str_offset;
	int		str_end;

	if (s1 == NULL || set == NULL)
		return (NULL);
	str_offset = offset_str(s1, set);
	str_end = end_str(s1, set);
	str = ft_substr(s1, str_offset, (str_end - str_offset));
	return (str);
}

static int	offset_str(char const *s1, char const *set)
{
	int		i;

	i = 0;
	while (s1[i] != '\0')
	{
		if (set_comp(s1, set, i) == 1)
			i++;
		else
			return (i);
	}
	return (0);
}

static int	set_comp(char const *s1, char const *set, int i)
{
	int	j;

	j = 0;
	while (set[j] != '\0')
	{
		if (set[j] == s1[i])
			return (1);
		j++;
	}
	return (0);
}

static int	end_str(char const *s1, char const *set)
{
	int	i;

	i = ft_strlen(s1);
	while (i > 0)
	{
		if (s1[i] == '\0' || set_comp(s1, set, i) == 1)
			i--;
		else
			return (i +1);
	}
	return (0);
}
