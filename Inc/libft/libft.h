/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgalvez- <fgalvez-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 18:55:21 by fgalvez-          #+#    #+#             */
/*   Updated: 2024/12/05 14:53:53 by fgalvez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <unistd.h>
# include <stddef.h>
# include <stdio.h>
# include <stdlib.h>

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}	t_list;

int		ft_strlen(const char *str);
void	*ft_memcpy(void *dest, const void *src, size_t n);
char	*ft_strdup(const char *s1);
void	*ft_calloc(size_t count, size_t size);
void	ft_bzero(void *s, size_t n);
t_list	*ft_lstnew(void *content);
t_list	*ft_lstlast(t_list *lst);
void	ft_lstadd_back(t_list **lst, t_list *new);
int		ft_lstsize(t_list *lst);
int		ft_isspace(char c);
char	*ft_strchr(const char *str, int x);
char	*ft_strndup(const char *s, size_t n);
size_t	ft_strnlen(const char *s, size_t maxlen);
int		ft_isalpha(int x);
int		ft_isalnum(int c);
int		ft_strcspn(char *str, char c);
char	*ft_strndup_no_nul(const char *s, size_t n);
char	*ft_itoa(int n);
int		ft_intlen(int n);
char	*ft_strjoin(const char *s1, const char *s2);
void	ft_putstr(char *str);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
int		ft_strcmp(const char *s1, const char *s2);
void	*ft_realloc(void *ptr, size_t old_size, size_t new_size);
void	*ft_free_split(char **s);
void	ft_putstrendl(char *str);
int		ft_atoi(const char *nptr);
int		ft_isnum(const char *str);
int		ft_isdigit(int x);
void	ft_putendl_fd(char *str, int fd);
void	ft_putstr_fd(const char *str, int fd);
char	*ft_substr(const char *s, unsigned int start, size_t len);
char	**ft_split(char const *s, char c);
void	ft_putchar_fd(char c, int fd);
#endif
