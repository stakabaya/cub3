/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stakabay <stakabay@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/22 16:24:28 by stakabay          #+#    #+#             */
/*   Updated: 2020/08/25 15:16:06 by stakabay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*sub;
	size_t	s_len;

	if (s == NULL)
		return (NULL);
	s_len = ft_strlen(s);
	if (s_len < start)
		len = 0;
	else if (s_len - start < len)
		len = s_len - start;
	sub = malloc(len + 1);
	if (sub == NULL)
		return (NULL);
	ft_memcpy(sub, s + start, len);
	*(sub + len) = '\0';
	return (sub);
}

int		fail(char **sta, char **buf)
{
	if (sta != NULL)
	{
		free(*sta);
		*sta = NULL;
	}
	if (buf != NULL)
	{
		free(*buf);
		*buf = NULL;
	}
	return (-1);
}

int		join_sta(char **sta, char *buf)
{
	char	*tmp;

	if (!*sta)
		if (!(*sta = ft_strdup("")))
			return (0);
	if (!(tmp = ft_strjoin(*sta, buf)))
		return (0);
	free(*sta);
	*sta = tmp;
	return (1);
}

int		join_line(char **line, char **sta, char *ptr)
{
	char	*tmp;

	if (!(*line = ft_substr(*sta, 0, ptr - *sta)))
	{
		free(*sta);
		*sta = NULL;
		return (-1);
	}
	if (ptr == 0)
	{
		free(*sta);
		*sta = NULL;
		return (0);
	}
	if (!(tmp = ft_strdup(ptr + 1)))
	{
		free(*sta);
		*sta = NULL;
		return (-1);
	}
	free(*sta);
	*sta = tmp;
	return (1);
}

int		get_next_line(int fd, char **line)
{
	static char *sta[1024 + 1];
	char		*buf;
	char		*ptr;
	int			rc;

	if (fd < 0 || !line || BUFFER_SIZE < 1)
		return (-1);
	if (!(buf = malloc(BUFFER_SIZE + 1)))
		return (fail(&sta[fd], &buf));
	while ((rc = read(fd, buf, BUFFER_SIZE)) >= 0)
	{
		buf[rc] = '\0';
		if (!(join_sta(&sta[fd], buf)))
			return (fail(&sta[fd], &buf));
		if (((ptr = ft_strchr(sta[fd], '\n')) != 0) || rc == 0)
		{
			free(buf);
			return (join_line(line, &sta[fd], ptr));
		}
	}
	return (fail(&buf, &sta[fd]));
}
