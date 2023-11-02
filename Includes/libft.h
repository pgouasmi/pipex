/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgouasmi <pgouasmi@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 14:25:19 by chonorat          #+#    #+#             */
/*   Updated: 2023/08/20 18:59:23 by pgouasmi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <stdlib.h>
# include <unistd.h>
# include <stdint.h>
# include <stdarg.h>

# define BUFFER_SIZE 5

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}					t_list;

int			ft_isalpha(int c);
int			ft_isdigit(int c);
int			ft_isalnum(int c);
int			ft_isascii(int c);
int			ft_isprint(int c);
int			ft_isws(char c);
size_t		ft_strlen(const char *s);
void		*ft_memset(void *b, int c, size_t len);
void		ft_bzero(void *s, size_t n);
void		*ft_memcpy(void *dst, const void *src, size_t n);
void		*ft_memmove(void *dst, const void *src, size_t len);
size_t		ft_strlcpy(char *dst, const char *src, size_t dstsize);
size_t		ft_strlcat(char *dst, const char *src, size_t dstsize);
int			ft_toupper(int c);
int			ft_tolower(int c);
char		*ft_strchr(const char *s, int c);
char		*ft_strrchr(const char *s, int c);
int			ft_strncmp(const char *s1, const char *s2, size_t n);
void		*ft_memchr(const void *s, int c, size_t n);
int			ft_memcmp(const void *s1, const void *s2, size_t n);
char		*ft_strnstr(const char *haystack, const char *needle, size_t len);
int			ft_atoi(const char *str);
void		*ft_calloc(size_t count, size_t size);
char		*ft_strdup(const char *s1);
int			ft_strcmp(const char *s1, const char *s2);

char		*ft_substr(char const *s, unsigned int start, size_t len);
char		*ft_strjoin(char const *s1, char const *s2);
char		*ft_strtrim(char const *s1, char const *set);
char		**ft_split(char const *s, char c);
char		*ft_itoa(int n);
char		*ft_strmapi(char const *s, char (*f)(unsigned int, char));
void		ft_striteri(char *s, void (*f)(unsigned int, char *));
int			ft_putchar_fd(char c, int fd);
int			ft_putstr_fd(char *s, int fd);
int			ft_putendl_fd(char *s, int fd);
int			ft_putnbr_fd(int n, int fd);

size_t		ft_arr_size(char **arr);
char		**ft_arr_copy(char **envp, size_t size);
long		ft_char_index(char *str, int c);

t_list		*ft_lstnew(void *content);
void		ft_lstadd_front(t_list **lst, t_list *new);
int			ft_lstsize(t_list *lst);
t_list		*ft_lstlast(t_list *lst);
void		ft_lstadd_back(t_list **lst, t_list *new);
void		ft_lstdelone(t_list *lst, void (*del)(void *));
void		ft_lstclear(t_list **lst, void (*del)(void *));
void		ft_lstiter(t_list *lst, void (*f)(void *));
t_list		*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *));

int			ft_printf(const char *str, ...);
const char	*ft_search_arg(va_list arg, const char *format, size_t *char_count);
const char	*ft_puttext(size_t *char_count, const char *format);
void		ft_putchar_pf(int c, size_t *char_count);
void		ft_putnbr_base_p(size_t n, const char *base, size_t *char_count);
void		ft_putnbr_base(long long int n, const char *base,
				size_t *char_count);
void		ft_putstr_pf(const char *s, size_t *char_count);

int			ft_dprintf(int fd, const char *format, ...);
const char	*ft_puttext_fd(size_t *char_count, const char *format, int fd);
const char	*ft_search_arg_fd(va_list arg, const char *format,
				size_t *char_count, int fd);
void		ft_dputnbr_base(long long int n, const char *base,
				size_t *char_count, int fd);
void		ft_putchar_dpf(int c, size_t *char_count, int fd);
void		ft_putnbr_base_dp(size_t n, const char *base,
				size_t *char_count, int fd);
void		ft_putstr_dpf(const char *s, size_t *char_count, int fd);

char		*get_next_line(int fd);
size_t		ft_strlen_gnl(char *s);
int			check_nl(char *stash);
char		*malloc_free(int size, char *to_free);
char		*ft_strchr_gnl( char *s, int c);
char		*ft_strjoin_gnl(char *buffer, char *stash);
char		*send_to_line(char *stash);
char		*stash_ready(char *stash);
char		*read_save(int fd, char *stash);

void		ft_free_null(char **str);
char		*strjoin_free_first(char **s1, char *s2);
char		*strjoin_free_both(char *s1, char *s2);

#endif
