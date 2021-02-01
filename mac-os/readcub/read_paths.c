/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_paths.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stakabay <stakabay@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/17 11:20:02 by stakabay          #+#    #+#             */
/*   Updated: 2021/01/26 00:15:02 by stakabay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "readcub.h"

unsigned char	ft_input_papth(t_game *game, unsigned char rflag,\
								char **str, int flagnum)
{
	if (rflag & flagnum)
		ft_error(0, -1, "invalid path");
	if (flagnum == NOFLAG)
		game->cub.nopath = str[1];
	else if (flagnum == SOFLAG)
		game->cub.sopath = str[1];
	else if (flagnum == WEFLAG)
		game->cub.wepath = str[1];
	else if (flagnum == EAFLAG)
		game->cub.eapath = str[1];
	else if (flagnum == SFLAG)
		game->cub.sppath = str[1];
	rflag |= flagnum;
	return (rflag);
}

unsigned char	ft_compass(t_game *game, char *line,\
							int count, unsigned char rflag)
{
	char		**str;

	str = ft_split(line, ' ');
	count = 0;
	while (str[count] != NULL)
		count++;
	if (count != 2)
		ft_error(0, -1, "invalid path");
	if (!(ft_memcmp(str[0], "NO\0", 3)))
		rflag = ft_input_papth(game, rflag, str, NOFLAG);
	else if (!(ft_memcmp(str[0], "SO\0", 3)))
		rflag = ft_input_papth(game, rflag, str, SOFLAG);
	else if (!(ft_memcmp(str[0], "WE\0", 3)))
		rflag = ft_input_papth(game, rflag, str, WEFLAG);
	else if (!(ft_memcmp(str[0], "EA\0", 3)))
		rflag = ft_input_papth(game, rflag, str, EAFLAG);
	else if (!(ft_memcmp(str[0], "S\0", 3)))
		rflag = ft_input_papth(game, rflag, str, SFLAG);
	free(str);
	return (rflag);
}
