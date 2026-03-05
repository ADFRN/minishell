/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afournie <afournie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 10:25:43 by afournie          #+#    #+#             */
/*   Updated: 2025/12/16 14:06:12 by afournie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <stdarg.h>
# include <stdlib.h>
# include <unistd.h>

# define BUFFER_SIZE 42
# define FORMAT_CHAR 'c'
# define FORMAT_STR 's'
# define FORMAT_POINT 'p'
# define FORMAT_DECIMAL 'd'
# define FORMAT_INT 'i'
# define FORMAT_UDESC 'u'
# define FORMAT_HEXALOW 'x'
# define FORMAT_HEXAUPP 'X'
# define FORMAT_PERCENT '%'

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}					t_list;

/* ************************************************************************** */
/*                                                                            */
/*                         Part 1 - Libc functions                            */
/*                                                                            */
/* ************************************************************************** */

int					ft_isalpha(int c);
int					ft_isdigit(int c);
int					ft_isalnum(int c);
int					ft_isascii(int c);
int					ft_isprint(int c);
size_t				ft_strlen(const char *s);
void				*ft_memset(void *b, int c, size_t len);
void				ft_bzero(void *s, size_t n);
void				*ft_memcpy(void *dst, const void *src, size_t n);
void				*ft_memmove(void *dst, const void *src, size_t len);
size_t				ft_strlcpy(char *dst, const char *src, size_t size);
size_t				ft_strlcat(char *dst, const char *src, size_t size);
int					ft_toupper(int c);
int					ft_tolower(int c);
char				*ft_strchr(const char *s, int c);
char				*ft_strrchr(const char *s, int c);
int					ft_strncmp(const char *s1, const char *s2, size_t n);
void				*ft_memchr(const void *s, int c, size_t n);
int					ft_memcmp(const void *s1, const void *s2, size_t n);
char				*ft_strnstr(const char *big, const char *little,
						size_t len);
int					ft_atoi(const char *str);
void				*ft_calloc(size_t nmemb, size_t size);
char				*ft_strdup(const char *s1);

/* ************************************************************************** */
/*                                                                            */
/*                     Part 2 - Additional functions                          */
/*                                                                            */
/* ************************************************************************** */

char				*ft_substr(char const *s, unsigned int start, size_t len);
char				*ft_strjoin(const char *s1, const char *s2);
char				*ft_strtrim(char const *s1, char const *set);
char				**ft_split(char const *s, char c);
char				*ft_itoa(int n);
char				*ft_strmapi(char const *s, char (*f)(unsigned int, char));
void				ft_striteri(char *s, void (*f)(unsigned int, char *));
void				ft_putchar_fd(char c, int fd);
void				ft_putstr_fd(char *s, int fd);
void				ft_putendl_fd(char *s, int fd);
void				ft_putnbr_fd(int n, int fd);

/* ************************************************************************** */
/*                                                                            */
/*                                Bonus part                                  */
/*                                                                            */
/* ************************************************************************** */

t_list				*ft_lstnew(void *content);
void				ft_lstadd_front(t_list **lst, t_list *new);
int					ft_lstsize(t_list *lst);
t_list				*ft_lstlast(t_list *lst);
void				ft_lstadd_back(t_list **lst, t_list *new);
void				ft_lstdelone(t_list *lst, void (*del)(void *));
void				ft_lstclear(t_list **lst, void (*del)(void *));
void				ft_lstiter(t_list *lst, void (*f)(void *));
t_list				*ft_lstmap(t_list *lst, void *(*f)(void *),
						void (*del)(void *));

/* ************************************************************************** */
/*                                                                            */
/*                             GET_NEXT_LINE                                  */
/*                                                                            */
/* ************************************************************************** */

char				*get_next_line(int fd);

/* ************************************************************************** */
/*                                                                            */
/*                                 PRINTF                                     */
/*                                                                            */
/* ************************************************************************** */

void				ft_print(const char s, va_list *arg, int *count);
int					ft_printf(const char *s, ...);
int					ft_is_format(const char s);
int					ft_putnbr_hexa_low(unsigned long n);
int					ft_putnbr_hexa_up(unsigned int n);
int					ft_putnbr_udesc(unsigned int n);
int					ft_print_ptr(void *adress);
int					ft_putstr(char *s);
int					ft_putnbr(int n);

#endif
