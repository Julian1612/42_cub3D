/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jschneid <jschneid@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 09:19:35 by jschneid          #+#    #+#             */
/*   Updated: 2023/02/08 14:42:23 by jschneid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# include <fcntl.h>
# include <stdlib.h>
# include <unistd.h>
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1
# endif

char	*get_next_line(int fd);
char	*get_buffer(char *buffer, int fd);
char	*cut_buffer(char *buffer, char **line);
char	*gnl_strchr(char const *s, int c);
char	*gnl_strjoin(char *s1, char *s2);
char	*gnl_substr(char const *s, unsigned int start, size_t len);
char	*gnl_strdup(const char *s1);
size_t	gnl_strlcpy(char *dst, const char *src, size_t destsize);
size_t	gnl_strlen(const char *a);

#endif
