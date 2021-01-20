/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stakabay <stakabay@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/04 18:01:22 by stakabay          #+#    #+#             */
/*   Updated: 2020/07/15 20:06:16 by stakabay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	unsigned char	*dst2;
	unsigned char	*src2;

	if (dst <= src)
		ft_memcpy(dst, src, len);
	else
	{
		dst2 = (unsigned char *)dst + (len - 1);
		src2 = (unsigned char *)src + (len - 1);
		while (len--)
			*dst2-- = *src2--;
	}
	return (dst);
}
