/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tripham <tripham@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 01:01:11 by caonguye          #+#    #+#             */
/*   Updated: 2025/04/18 21:16:23 by tripham          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <unistd.h>
# include <stdlib.h>
# include <stddef.h>
# include <limits.h>

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}	t_list;

int		ft_isalpha(int c);
int		ft_isdigit(int c);
int		ft_isalnum(int c);
int		ft_isprint(int c);
int		ft_isascii(int c);
int		ft_isallspace(char c);
int		ft_wholespace(char *str);
int		ft_is_dquote(char c);
int		ft_rd_op(char *str, int id);
int		ft_toupper(int c);
int		ft_tolower(int c);

int		ft_2d_len(char **arr);
int		ft_char_cnt_2d(char *src, char c);
int		ft_memcmp(const void *s1, const void *s2, size_t n);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
int		ft_strcmp(const char *s1, const char *s2);
int		ft_strnstr_2d(char **big, const char *little, int len);
int		ft_atoi(const char *nptr);
int		ft_append(char **s1, char **s2);
int		ft_append_2d(char ***s1, char *s2);
int		ft_free_process_2d(char **arr, size_t cur);
int		ft_free_process_3d(char ***arr, size_t cur);
void	ft_free_2d(void **arr);
void	ft_free_3d(void ***arr);
void	ft_free_2d_int(int **arr, int len);
void	ft_free_3d_int(int ***arr, int len);
void	*ft_calloc(size_t nmemb, size_t len);
void	*ft_memset(void *s, int c, size_t n);
void	*ft_memcpy(void *dest, const void *src, size_t n);
void	*ft_memmove(void *dest, const void *src, size_t n);
void	*ft_memchr(const void *s, int c, size_t n);
void	ft_bzero(void *s, size_t n);
void	ft_striteri(char *s, void (*f)(unsigned int, char*));
char	*ft_strnenv(const char *big, const char *little, size_t len);
char	*ft_strchr(const char *s, int c);
int		ft_strichr(const char *s, int c);
char	*ft_strrchr(const char *s, int c);
char	*ft_strdup(const char *s);
char	*ft_strnstr(const char *big, const char *little, size_t len);
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	*ft_custom_substr(char *s, unsigned int start, size_t len, char *c);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strjoin_free(char *s1, char *s2);
char	*ft_strtrim(char const *s1, char const *set);
char	*ft_itoa(int n);
char	*ft_strmapi(char const *s, char (*f)(unsigned int, char));
char	*ft_char_eli(char *string, char c);
char	*ft_substr_eli(char *s, int start, int len, char c);
size_t	ft_strlcpy(char *dst, const char *src, size_t len);
size_t	ft_strlcat(char *dst, const char *src, size_t len);
size_t	ft_strlen(const char *s);
int		ft_sub_2d(char **org, char **des, int start, int len);
char	**ft_split(char const *s, char c);
int		ft_append_2d(char ***s1, char *s2);

t_list	*ft_lstnew(void *content);
void	ft_lstadd_front(t_list **lst, t_list *new);
void	ft_lstadd_back(t_list **lst, t_list *new);
int		ft_lstlen(t_list *lst);
t_list	*ft_lstlast(t_list *lst);
void	ft_lstdelone(t_list *lst, void (*del)(void*));
void	ft_lstclear(t_list **lst, void (*del)(void*));
void	ft_lstiter(t_list *lst, void (*f)(void*));
t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *));
int		ft_atol_safe(const char *s, long *out);

#endif
