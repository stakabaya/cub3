/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stakabay <stakabay@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/17 11:29:28 by stakabay          #+#    #+#             */
/*   Updated: 2021/01/19 23:09:28 by stakabay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "readcub.h"

void		set_sprite(t_game *game)
{
	int		i;
	int		j;

	game->sprite = malloc(sizeof(t_sprite) * game->sprite_num);
	game->sprite_num = 0;
	i = 1;
	while (i < game->cub.rows + 1)
	{
		j = 1;
		while (j < game->cub.cols + 1)
		{
			if (game->cub.bigmap[i][j] == '2')
			{
				game->sprite[game->sprite_num].x = j - 1 + 0.5;
				game->sprite[game->sprite_num].y = i - 1 + 0.5;
				game->sprite_num++;
			}
			j++;
		}
		i++;
	}
}

void		make_map(t_game *game, int fd)
{
	int		rt;
	char	*line;
	int		j;
	int		max;

	game->cub.rows = 0;
	max = 0;
	while ((rt = get_next_line(fd, &line)) >= 0)
	{
		j = 0;
		while (line[j])
		{
			game->cub.map[game->cub.rows][j] = line[j];
			j++;
		}
		game->cub.map[game->cub.rows][j] = '\0';
		max = ft_strlen(line);
		if (++game->cub.rows > 200 || max > 200)
			ft_error(0, 0, "too big map");
		game->cub.cols = (game->cub.cols < max) ? max : game->cub.cols;
		if (rt == 0)
			break ;
	}
	close(fd);
}

void		make_bigmap(t_game *game)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (i < game->cub.rows + 2)
	{
		j = 0;
		while (j < game->cub.cols + 2)
		{
			game->cub.bigmap[i][j] = 'X';
			j++;
		}
		game->cub.bigmap[i][j] = '\0';
		i++;
	}
}

void		set_map(t_game *game)
{
	int		playerflag;
	int		i;
	int		j;

	i = 1;
	playerflag = 0;
	while (i < game->cub.rows + 1)
	{
		j = 1;
		while (game->cub.map[i - 1][j - 1] != '\0')
		{
			game->cub.bigmap[i][j] = game->cub.map[i - 1][j - 1];
			divide(game, i, j, playerflag);
			j++;
		}
		i++;
	}
}
