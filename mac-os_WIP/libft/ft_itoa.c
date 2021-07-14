/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stakabay <stakabay@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/15 19:55:59 by stakabay          #+#    #+#             */
/*   Updated: 2020/08/27 08:22:04 by stakabay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	char	*setnum(char *num, int keta, int n)
{
	int flag;

	flag = 1;
	if (n < 0)
	{
		num[0] = '-';
		n *= -1;
		flag = 0;
	}
	num[keta--] = '\0';
	while (keta > 0)
	{
		num[keta--] = (n % 10) + '0';
		n /= 10;
	}
	if (flag == 1)
		num[0] = (n % 10) + '0';
	return (num);
}

char			*ft_itoa(int n)
{
	int		keta;
	int		tmp;
	char	*num;

	if (n == -2147483648)
	{
		if (!(num = (char *)ft_calloc(12, sizeof(char))))
			return (NULL);
		setnum(num, 10, -214748364);
		num[10] = '8';
		return (num);
	}
	keta = 1;
	if (n < 0)
		keta++;
	tmp = n;
	while (tmp /= 10)
		keta++;
	if (!(num = malloc(keta + 1)))
		return (NULL);
	return (setnum(num, keta, n));
}
