/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stakabay <stakabay@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/22 16:34:15 by stakabay          #+#    #+#             */
/*   Updated: 2021/01/19 23:43:56 by stakabay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

int		get_next_line(int fd, char **line);
int		join_line(char **line, char **sta, char *ptr);
int		join_sta(char **sta, char *buf);
int		fail(char **sta, char **buf);
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strdup(const char *s);
char	*ft_strchr(const char *s, int c);
size_t	ft_strlen(const char *s);
void	*ft_memcpy(void *buf1, const void *buf2, size_t n);

# define BUFFER_SIZE 1000

#endif
