/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jschneid <jschneid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/12 14:27:41 by jschneid          #+#    #+#             */
/*   Updated: 2022/06/03 14:11:53 by jschneid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		**ft_split(char const *s, char c);
static char	**get_mem(char const *s, char c);
static int	count_words(char const *s, char c);
static void	get_strings(char const *s, char c, char **array);
static void	ft_free(char **array, int j);

char	**ft_split(char const *s, char c)
{
	char	**array;

	if (s == NULL)
		return (NULL);
	array = get_mem(s, c);
	return (array);
}

static char	**get_mem(char const *s, char c)
{
	char	**array;

	array = (char **) malloc((count_words(s, c) + 1) * sizeof(char *));
	if (array == NULL)
		return (NULL);
	get_strings(s, c, array);
	return (array);
}

static int	count_words(char const *s, char c)
{
	unsigned long	i;
	int				word;

	i = 0;
	word = 0;
	while (s[i] != '\0')
	{
		if (s[i] != c && (s[i + 1] == c || (s[i + 1] == '\0')))
			word++;
		i++;
	}
	return (word);
}

static void	get_strings(char const *s, char c, char **array)
{
	int		i;
	int		j;
	int		word_len;

	i = 0;
	j = 0;
	word_len = 0;
	while (s[i] != '\0')
	{
		if (s[i] != c)
			word_len++;
		if (s[i] != c && (s[i + 1] == c || (s[i + 1] == '\0')))
		{
			array[j] = ft_substr(s, (i + 1) - word_len, word_len);
			if (array[j] == NULL)
			{
				ft_free (array, j);
			}
			word_len = 0;
			j++;
		}
		i++;
	}
	array[j] = NULL;
}

static void	ft_free(char **array, int j)
{
	int	i;

	i = 0;
	while (i <= j)
	{
		free (array[i]);
		i++;
	}
}
