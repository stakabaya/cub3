/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stakabay <stakabay@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/15 20:35:37 by stakabay          #+#    #+#             */
/*   Updated: 2020/07/15 20:36:19 by stakabay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char	*str;
	int		len;

	str = (char *)s;
	if (c == 0)
		return (str + ft_strlen(s));
	len = ft_strlen(s);
	while (len-- != 0)
	{
		if (*(str + len) == c)
			return (str + len);
	}
	return (0);
}
