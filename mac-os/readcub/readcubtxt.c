/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readcubtxt.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stakabay <stakabay@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/05 23:28:33 by stakabay          #+#    #+#             */
/*   Updated: 2021/01/19 23:39:57 by stakabay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include "readcub.h"

int			serch(int x, int y, t_game *game, int flag)
{
	if (flag == -1)
		return (-1);
	if (game->cub.bigmap[y][x] == '1')
		return (1);
	if (game->cub.bigmap[y][x] == 'R')
		return (1);
	if (game->cub.bigmap[y][x] == 'X')
		return (-1);
	game->cub.bigmap[y][x] = 'R';
	flag = serch(x + 1, y, game, flag);
	flag = serch(x - 1, y, game, flag);
	flag = serch(x, y + 1, game, flag);
	flag = serch(x, y - 1, game, flag);
	return (flag);
}

int			open_file(t_game *game, char **argv, int argc)
{
	int		fd;
	int		len;

	if (argc == 3 && (ft_memcmp(argv[2], "--save\0", 7) == 0))
		game->bmp = 1;
	else if (argc == 3)
		ft_error(0, -1, "invalid arguments");
	len = ft_strlen(argv[1]);
	if (ft_memcmp((argv[1] + (len - 4)), ".cub", 4) != 0)
		ft_error(0, -1, "invalid extention");
	if ((fd = open(argv[1], O_RDONLY | O_DIRECTORY)) != -1)
		ft_error(0, -1, ".cub is a directory");
	if ((fd = open(argv[1], O_RDONLY)) == -1)
		ft_error(0, -1, "open error");
	return (fd);
}

int			readcubtxt(t_game *game, char **argv, int argc)
{
	int		fd;
	int		flag;

	game->cub.cols = 0;
	game->sprite_num = 0;
	fd = open_file(game, argv, argc);
	elements_ot_map(game, fd);
	make_map(game, fd);
	make_bigmap(game);
	set_map(game);
	set_sprite(game);
	flag = 1;
	if ((flag = serch(game->cub.player_x, \
		game->cub.player_y, game, flag)) == -1)
		ft_error(0, -1, "incorrect map");
	return (0);
}
