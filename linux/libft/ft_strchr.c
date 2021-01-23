/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stakabay <stakabay@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/15 20:20:29 by stakabay          #+#    #+#             */
/*   Updated: 2020/07/15 20:21:11 by stakabay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	char *str;

	str = (char *)s;
	if (c == 0)
		return (str + ft_strlen(s));
	while (*str != '\0')
	{
		if (*str == c)
			return (str);
		str++;
	}
	return (0);
}
