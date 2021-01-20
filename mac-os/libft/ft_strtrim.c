/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stakabay <stakabay@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/15 19:08:39 by stakabay          #+#    #+#             */
/*   Updated: 2020/07/15 19:09:50 by stakabay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	int		s1_len;
	int		size;
	int		start;
	int		end;
	char	*ans;

	if (s1 == NULL)
		return (NULL);
	s1_len = ft_strlen(s1);
	if (set == NULL)
		return (ft_substr(s1, 0, s1_len));
	size = s1_len;
	start = 0;
	while (ft_strchr(set, s1[start]) && size-- > 0)
		start++;
	end = s1_len;
	while (ft_strchr(set, s1[end - 1]) && size-- > 0)
		end--;
	if (size == 0)
		return (ft_strdup(""));
	ans = ft_substr(s1, start, end - start);
	if (ans == NULL)
		return (NULL);
	return (ans);
}
