/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julberna <julberna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 09:10:21 by iusantos          #+#    #+#             */
/*   Updated: 2024/02/02 13:43:19 by iusantos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <unistd.h>
# include <stdlib.h>
# include <stdarg.h>

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}				t_list;

void		ft_putchar_fd(char c, int fd);
void		ft_putstr_fd(char *s, int fd);
void		ft_putendl_fd(char *s, int fd);
int			ft_isalpha(int c);
int			ft_isdigit(int c);
int			ft_isalnum(int c);
int			ft_isascii(int c);
int			ft_isprint(int c);
int			ft_notspace(int c);
size_t		ft_strlen(const char *s);
void		ft_bzero(void *s, size_t n);
void		*ft_memset(void *s, int c, size_t n);
void		*ft_memcpy(void *dest, const void *src, size_t n);
void		*ft_memmove(void *dest, const void *src, size_t n);
int			ft_memcmp(const void *s1, const void *s2, size_t n);
void		*ft_memchr(const void *s, int c, size_t n);
int			ft_tolower(int c);
int			ft_toupper(int c);
char		*ft_strchr(const char *s, int c);
char		*ft_strrchr(const char *s, int c);
int			ft_strncmp(const char *s1, const char *s2, size_t n);
int			ft_strcmp(const char *s1, const char *s2);
char		*ft_strnstr(const char *big, const char *little, size_t len);
int			ft_atoi(const char *nptr);
long long	ft_atoll(const char *nptr);
long		ft_atol(const char *nptr);
size_t		ft_strlcpy(char *dst, const char *src, size_t size);
size_t		ft_strlcat(char *dst, const char *src, size_t size);
char		*ft_strdup(const char *s);
void		*ft_calloc(size_t nelem, size_t elsize);
char		*ft_substr(char const *s, unsigned int start, size_t len);
char		*ft_strjoin(char const *s1, char const *s2);
char		*ft_strtrim(char const *s1, char const *set);
char		**ft_split(char const *s, char c);
void		ft_putnbr_fd(int n, int fd);
void		ft_striteri(char *s, void (*f)(unsigned int, char*));
char		*ft_strmapi(char const *s, char (*f)(unsigned int, char));
char		*ft_itoa(int n);
t_list		*ft_lstnew(void *content);
void		ft_lstadd_front(t_list **lst, t_list *new);
int			ft_lstsize(t_list *lst);
t_list		*ft_lstlast(t_list *lst);
void		ft_lstadd_back(t_list **lst, t_list *new);
void		ft_lstdelone(t_list *lst, void (*del)(void *));
void		ft_lstclear(t_list **lst, void (*del)(void *));
void		ft_lstiter(t_list *lst, void (*f)(void *));
t_list		*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *));
int			count_word(const char *s, char c); // organizar isso aqui depois

/**** get_next_line ****/

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 4096
# endif //BUFFER_SIZE

char		*get_next_line(int fd);
char		*gnl_strjoin(char *s1, char *s2);
int			find_first_newline(char *s1);

/**** ft_printf ****/
int			ft_printf(const char *format, ...);
size_t		print_accordingly(char c, va_list args);
/* %c and %%*/
size_t		prtf_putchar(char c);
/* %s */
size_t		prtf_putstr(char *str);
/* %d and %i */
size_t		print_int(int nbr);
void		write_str(long n, char *str, size_t length);
/*  %u */
char		*ft_uitoa(unsigned int n);
size_t		print_uint(unsigned int nbr);
/*  %x and %X */
void		write_hex_str(unsigned long n, char *str, size_t length, char c);
char		*uitohex(unsigned long n, char c);
size_t		print_hex(unsigned long n, char c);
/*  %p */
void		write_pref_hex_str(unsigned long n, char *str, size_t length);
char		*ultoa(unsigned long n);
size_t		print_voidp(unsigned long p);
/* utils */
size_t		count_digit_base(unsigned long n, unsigned int base);

#endif
