/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stakabay <stakabay@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/15 16:44:56 by stakabay          #+#    #+#             */
/*   Updated: 2020/07/15 18:13:01 by stakabay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

#define NOTSEP 1
#define SEP 0

static	void	ft_free(char **arr, int i)
{
	while (0 <= i)
		free(arr[i--]);
	return ;
}

static	int		sp(char **arr, char *s, char c)
{
	int i;
	int j;
	int start;

	i = 0;
	j = 0;
	while (s[j])
	{
		while (s[j] == c && s[j])
			j++;
		start = j;
		while (s[j] != c && s[j])
			j++;
		if (s[j - 1] != c)
		{
			if (!(arr[i] = ft_substr(s, start, j - start)))
			{
				ft_free(arr, i - 1);
				return (1);
			}
			i++;
		}
	}
	return (0);
}

static	int		arrcountcheck(const char *s, char c)
{
	int	flag;
	int arrcount;

	arrcount = 0;
	if (*s == 0)
		return (arrcount);
	if (*s++ != c && *s)
	{
		flag = NOTSEP;
		arrcount++;
	}
	else
		(flag = SEP);
	while (*s)
	{
		if (flag == SEP && *s != c)
		{
			flag = NOTSEP;
			arrcount++;
		}
		if (flag == NOTSEP && *s == c)
			flag = SEP;
		s++;
	}
	return (arrcount);
}

char			**ft_split(char const *s, char c)
{
	int		arrcount;
	char	**arr;

	arrcount = 0;
	if (s == NULL)
		return (NULL);
	arrcount = arrcountcheck(s, c);
	if (!(arr = (char **)malloc(sizeof(char *) * (arrcount + 1))))
		return (NULL);
	if (s != NULL && arrcount != 0)
	{
		if (sp(arr, (char *)s, c))
		{
			free(arr);
			return (NULL);
		}
	}
	arr[arrcount] = NULL;
	return (arr);
}
