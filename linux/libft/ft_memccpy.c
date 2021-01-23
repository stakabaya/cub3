/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stakabay <stakabay@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/04 18:00:26 by stakabay          #+#    #+#             */
/*   Updated: 2020/07/15 20:00:10 by stakabay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dest, const void *src, int c, size_t n)
{
	unsigned char		*dest2;
	const unsigned char *src2;
	unsigned char		c2;

	dest2 = dest;
	src2 = src;
	c2 = c;
	while (n != 0)
	{
		if (*src2 == c2)
		{
			*dest2 = *src2;
			return (dest2 + 1);
		}
		*dest2 = *src2;
		n--;
		dest2++;
		src2++;
	}
	return (NULL);
}
