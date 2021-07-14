/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stakabay <stakabay@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/22 16:42:22 by stakabay          #+#    #+#             */
/*   Updated: 2021/02/02 02:09:06 by stakabay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char		*ft_strjoin_gnl(char const *s1, char const *s2)
{
	int		s1_len;
	int		s2_len;
	char	*join;

	if (s1 == NULL || s2 == NULL)
		return (NULL);
	s1_len = ft_strlen_gnl(s1);
	s2_len = ft_strlen_gnl(s2);
	if (!(join = malloc(s1_len + s2_len + 1)))
		return (NULL);
	ft_memcpy_gnl(join, s1, s1_len);
	ft_memcpy_gnl(join + s1_len, s2, s2_len);
	*(join + s1_len + s2_len) = 0;
	return (join);
}

char		*ft_strdup_gnl(const char *s)
{
	char	*dup;
	int		len;

	len = ft_strlen_gnl(s);
	dup = malloc(len + 1);
	if (dup == NULL)
		return (NULL);
	else
		return (ft_memcpy_gnl(dup, s, len + 1));
}

char		*ft_strchr_gnl(const char *s, int c)
{
	char	*str;

	str = (char *)s;
	if (c == 0)
		return (str + ft_strlen_gnl(s));
	while (*str != '\0')
	{
		if (*str == c)
			return (str);
		str++;
	}
	return (0);
}

size_t		ft_strlen_gnl(const char *s)
{
	int		len;

	len = 0;
	while (*s++)
		len++;
	return (len);
}

void		*ft_memcpy_gnl(void *buf1, const void *buf2, size_t n)
{
	unsigned char		*tmp1;
	const unsigned char	*tmp2;

	if (buf1 == NULL && buf2 == NULL)
		return (NULL);
	tmp1 = buf1;
	tmp2 = buf2;
	while (n != 0)
	{
		*tmp1 = *tmp2;
		n--;
		tmp1++;
		tmp2++;
	}
	return (buf1);
}
