/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stakabay <stakabay@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/15 20:27:58 by stakabay          #+#    #+#             */
/*   Updated: 2020/07/15 20:31:00 by stakabay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char			*p;
	unsigned int	len;
	unsigned int	i;

	if (s == NULL)
		return (NULL);
	len = ft_strlen(s);
	if (!(p = (char *)malloc(len + 1)))
		return (NULL);
	i = 0;
	while (i < len)
	{
		if (f == NULL)
			p[i] = s[i];
		else
			p[i] = (*f)(i, s[i]);
		i++;
	}
	p[len] = '\0';
	return (p);
}
