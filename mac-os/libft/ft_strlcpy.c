/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stakabay <stakabay@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/15 20:26:33 by stakabay          #+#    #+#             */
/*   Updated: 2020/07/15 20:26:52 by stakabay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t src_len;

	src_len = ft_strlen(src);
	if (dstsize == 0)
		return (src_len);
	while (1 < dstsize-- && *src != 0)
		*dst++ = *src++;
	*dst = 0;
	return (src_len);
}
