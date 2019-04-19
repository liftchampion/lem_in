/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shapka                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggerardy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/26 17:25:22 by ggerardy          #+#    #+#             */
/*   Updated: 2019/04/08 21:22:41 by ggerardy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <string.h>
# include "ft_types.h"
# include "ft_map.h"
# include "ft_string.h"
# include "ft_printf.h"

# define FT_ABS(x) (((x) >= 0) ? (x) : -(x))

ssize_t				ft_read(int fd, void *buf, size_t buf_size);

char				*ft_strsub_char_m(char **s, char c, int init_size);

int					free_ret(void *to_free, int ret);

void				ft_swap(void *a, void *b, size_t s);

int					ft_word_count(const char *str);

int					ft_get_next_line(int fd, char **line, int buff_size);

char				*ft_strset(char *b, int c, size_t size);

void				*ft_memset(void *b, int c, size_t len);

void				ft_bzero(void *b, size_t len);

void				*ft_memcpy(void *dst, const void *src, size_t n);

void				*ft_memccpy(void *dest, const void *src, int c, size_t n);

void				*ft_memmove(void *dest, const void *src, size_t n);

void				*ft_memchr(const void *str, int ch, size_t n);

int					ft_memcmp(const void *s1, const void *s2, size_t len);

size_t				ft_strlen(char const *s);

char				*ft_strdup(const char *src);

char				*ft_strcpy(char *dest, const char *src);

char				*ft_strncpy(char *dest, const char *src, size_t len);

size_t				ft_strlcpy(char *dest, const char *src, size_t size);

char				*ft_strcat(char *dest, const char *src);

char				*ft_strncat(char *dest, const char *src, size_t nb);

size_t				ft_strlcat(char *dest, const char *src, size_t size);

char				*ft_strchr(const char *str, int ch);

char				*ft_rstrchr(const char *str, int ch);

char				*ft_strrchr(const char *str, int ch);

char				*ft_strstr(const char *str, const char *to_find);

char				*ft_strnstr(const char *str, const char *to_find,
																size_t len);

int					ft_strcmp(const char *s1, const char *s2);

int					ft_strncmp(const char *s1, const char *s2, unsigned int n);

int					ft_atoi(const char *str);

int					ft_atoi_m(char **str);

long				ft_atoi_base_m(const char **str, int radix);

int					ft_isalpha(int c);

int					ft_isdigit(int c);

int					ft_isalnum(int c);

int					ft_isascii(int c);

int					ft_isprint(int c);

int					ft_toupper(int c);

int					ft_tolower(int c);

int					ft_pow(int nb, int power);

char				*ft_strrev(char *str);

int					ft_isspace(char c);

void				ft_print_arr(void *arr, int size_of, size_t len);

int					ft_is_in_charset(char c, char const *charset);

char				**ft_split_charset(char const *str, char const *charset);

void				ft_print_words_table(char const **tab);

void				ft_free_matrix(void **ptr, size_t n);

void				*ft_realloc(void *old_data, size_t prev_size,
														size_t new_size);

void		*ft_realloc_free(void *old_data, size_t prev_size, size_t new_size,
		void (*free_data)(void*));

void				*ft_memalloc(size_t size);

void				ft_memdel(void **ap);

char				*ft_strnew(size_t size);

void				ft_strdel(char **as);

void				ft_strclr(char *s);

void				ft_striter(char *s, void (*f)(char *));

void				ft_striteri(char *s, void (*f)(unsigned int, char *));

char				*ft_strmap(char const *s, char (*f)(char));

char				*ft_strmapi(char const *s, char (*f)(unsigned int, char));

int					ft_strequ(char const *s1, char const *s2);

int					ft_strnequ(char const *s1, char const *s2, size_t n);

char				*ft_strsub(char const *s, unsigned int start, size_t len);

char				*ft_strjoin(char const *s1, char const *s2);

char				*ft_strtrim(char const *s);

char				**ft_strsplit(char const *s, char c);

char				*ft_itoa(int n);

char				*ft_itoa_buf(int n, char *res);

void				ft_putchar(char c);

void				ft_putchar_u(int c);

void				ft_putstr(char const *s);

void				ft_putstr_u(int const *s);

void				ft_putendl(char const *s);

void				ft_putnbr(int n);

void				ft_putchar_fd(char c, int fd);

void				ft_putchar_u_fd(int c, int fd);

void				ft_putstr_fd(char const *s, int fd);

void				ft_putstr_u_fd(int const *s, int fd);

void				ft_putendl_fd(char const *s, int fd);

void				ft_putnbr_fd(int n, int fd);

typedef struct		s_list
{
	void			*content;
	size_t			content_size;
	struct s_list	*next;
}					t_list;

t_list				*ft_lstnew(void const *content, size_t content_size);

void				ft_lstdelone(t_list **alst, void (*del)(void *, size_t));

void				ft_lstdel(t_list **alst, void (*del)(void *, size_t));

void				ft_lstadd(t_list **alst, t_list *new);

void				ft_lstiter(t_list *lst, void (*f)(t_list *elem));

t_list				*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem));

char				*ft_ftoa(double num, int acc);

int					ft_intlen(long int nb);

char				*ft_tolower_str(char *str);

char				*ft_toupper_str(char *str);

char				ft_unilen(int u);

size_t				ft_strlen_u(const int *s, char f);

char				*ft_int_to_unicode(int n, char *bytes);

#endif
