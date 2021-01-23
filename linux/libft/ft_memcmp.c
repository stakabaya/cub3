/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stakabay <stakabay@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/04 21:19:11 by stakabay          #+#    #+#             */
/*   Updated: 2020/07/15 20:04:49 by stakabay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	const unsigned char *str1;
	const unsigned char *str2;

	str1 = (const unsigned char *)s1;
	str2 = (const unsigned char *)s2;
	while (--n && *str1 == *str2)
	{
		str1++;
		str2++;
	}
	return (*str1 - *str2);
}
