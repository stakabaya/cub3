/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stakabay <stakabay@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/15 20:33:56 by stakabay          #+#    #+#             */
/*   Updated: 2020/07/15 20:35:11 by stakabay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	neelen;
	char	*ptr;

	if (*needle == '\0')
		return ((char *)haystack);
	neelen = ft_strlen(needle);
	ptr = (char *)haystack;
	ptr = ft_strchr(haystack, *needle);
	while (ptr != NULL && (ptr - haystack) + neelen <= len)
	{
		if (ft_memcmp(ptr, needle, neelen) == 0)
			return (ptr);
		ptr = ft_strchr(ptr + 1, *needle);
	}
	return (NULL);
}
