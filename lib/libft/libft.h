/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jschneid <jschneid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 16:07:05 by jschneid          #+#    #+#             */
/*   Updated: 2022/08/17 15:22:44 by jschneid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H
# include <stdlib.h>
# include <unistd.h>
# include <stdarg.h>
# include <fcntl.h>
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1
# endif

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}					t_list;

int				ft_atoi(const char *nptr);
void			ft_bzero(void *s, size_t n);
void			*ft_calloc(size_t count, size_t size);
int				ft_isalnum(int i);
int				ft_isalpha(int i);
int				ft_isascii(int i);
int				ft_isdigit(int i);
int				ft_isprint(int i);
char			*ft_itoa(int n);
void			*ft_memchr(const void *s, int c, size_t n);
int				ft_memcmp(const void *s1, const void *s2, size_t n);
void			*ft_memcpy(void *dst, const void *src, size_t n);
void			*ft_memmove(void *dst, const void *src, size_t len);
void			*ft_memset(void *b, int c, size_t len);
void			ft_putchar_fd(char c, int fd);
void			ft_putendl_fd(char *s, int fd);
void			ft_putnbr_fd(int n, int fd);
void			ft_putstr_fd(char *s, int fd);
char			**ft_split(char const *s, char c);
char			*ft_strchr(const char *string, int value);
char			*ft_strdup(const char *s1);
void			ft_striteri(char *s, void (*f)(unsigned int, char*));
char			*ft_strjoin(char const *s1, char const *s2);
size_t			ft_strlcat(char *dst,
					const char *src, size_t size);
size_t			ft_strlcpy(char *dst, const char *src, size_t size);
size_t			ft_strlen(const char *a);
char			*ft_strmapi(char const *s, char (*f)(unsigned int, char));
int				ft_strncmp(const char *s1, const char *s2, size_t n);
char			*ft_strnstr(const char *haystack,
					const char *needle, size_t size);
char			*ft_strrchr(const char *string, int value);
char			*ft_strtrim(char const *s1, char const *set);
char			*ft_substr(char const *s, unsigned int start, size_t len);
int				ft_tolower(int c);
int				ft_toupper(int c);
t_list			*ft_lstnew(void *content);
void			ft_lstadd_front(t_list **lst, t_list *new);
int				ft_lstsize(t_list *lst);
t_list			*ft_lstlast(t_list *lst);
void			ft_lstadd_back(t_list **lst, t_list *new);
void			ft_lstdelone(t_list *lst, void (*del)(void *));
void			ft_lstclear(t_list **lst, void (*del)(void *));
void			ft_lstiter(t_list *lst, void (*f)(void *));
t_list			*ft_lstmap(t_list *lst, void *(*f)(void *),
					void (*del)(void *));

///////////////////////////////// get_next_line ////////////////////////////////

char			*get_next_line(int fd);
char			*get_buffer(char *buffer, int fd);
char			*cut_buffer(char *buffer, char **line);
char			*gnl_strchr(char const *s, int c);
char			*gnl_strjoin(char *s1, char *s2);
char			*gnl_substr(char const *s, unsigned int start, size_t len);
char			*gnl_strdup(const char *s1);
size_t			gnl_strlcpy(char *dst, const char *src, size_t destsize);
size_t			gnl_strlen(const char *a);

///////////////////////////////// ft_printf ////////////////////////////////////

int				ft_printf(const char *input_str, ...);
void			print_character(const char output_char);
int				write_string(const char *input_str, va_list arguments);
int				variable_check(const char *input_str,
					int index, va_list arguments);
int				output_character(va_list arguments);
int				output_string(va_list arguments);
int				output_numbers(va_list arguments);
int				output_integer(va_list arguments);
int				output_percent(void);
int				output_pointer_address(va_list arguments);
void			print_pointer_address(unsigned long long decimal_nbr);
int				output_lowercase_hexadecimal(va_list argument);
void			print_lowercase_hexadecimal(unsigned int decimal_nbr);
int				output_uppercase_hexadecimal(va_list arguments);
void			print_uppercase_hexadecimal(unsigned int decimal_nbr);
int				output_unsigned_integer(va_list arguments);
int				number_length_hexadecimal(unsigned long long numb);
long			number_length(long numb);
char			*get_string(long numb, char *str, long numb_len);

#endif
