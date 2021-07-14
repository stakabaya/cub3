/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stakabay <stakabay@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/04 18:01:22 by stakabay          #+#    #+#             */
/*   Updated: 2020/07/08 00:09:56 by stakabay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *buf1, const void *buf2, size_t n)
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
