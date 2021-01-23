/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stakabay <stakabay@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/15 16:56:34 by stakabay          #+#    #+#             */
/*   Updated: 2020/07/15 20:11:49 by stakabay         ###   ########.fr       */
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

void			ft_putnbr_fd(int n, int fd)
{
	int		keta;
	int		tmp;
	char	num[100];

	if (n == -2147483648)
	{
		setnum(num, 10, -214748364);
		num[10] = '8';
		write(fd, num, strlen(num));
		return ;
	}
	keta = 1;
	if (n < 0)
		keta++;
	tmp = n;
	while (tmp /= 10)
		keta++;
	setnum(num, keta, n);
	write(fd, num, strlen(num));
}
