/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_playerpos.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stakabay <stakabay@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/17 11:36:54 by stakabay          #+#    #+#             */
/*   Updated: 2021/01/23 22:36:20 by stakabay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "readcub.h"

int			ft_n(t_game *game, int playerflag, int i, int j)
{
	if (playerflag == 1)
	{
		perror("multiplayerstartpoint");
		exit(0);
	}
	game->cub.player_x = j - 1 + 0.5;
	game->cub.player_y = i - 1 + 0.5;
	game->player.rotation_angle = PI * 3 / 2;
	game->player.dir_x = 0;
	game->player.dir_y = -1;
	game->player.plane_x = 0.66;
	game->player.plane_y = 0;
	playerflag = 1;
	return (playerflag);
}

int			ft_w(t_game *game, int playerflag, int i, int j)
{
	if (playerflag == 1)
	{
		perror("multiplayerstartpoint");
		exit(0);
	}
	game->cub.player_x = j - 1 + 0.5;
	game->cub.player_y = i - 1 + 0.5;
	game->player.rotation_angle = PI;
	game->player.dir_x = -1;
	game->player.dir_y = 0;
	game->player.plane_x = 0;
	game->player.plane_y = -0.66;
	playerflag = 1;
	return (playerflag);
}

int			ft_s(t_game *game, int playerflag, int i, int j)
{
	if (playerflag == 1)
	{
		perror("multiplayerstartpoint");
		exit(0);
	}
	game->cub.player_x = j - 1 + 0.5;
	game->cub.player_y = i - 1 + 0.5;
	game->player.rotation_angle = PI / 2;
	game->player.dir_x = 0;
	game->player.dir_y = 1;
	game->player.plane_x = -0.66;
	game->player.plane_y = 0;
	playerflag = 1;
	return (playerflag);
}

int			ft_e(t_game *game, int playerflag, int i, int j)
{
	if (playerflag == 1)
	{
		perror("multiplayerstartpoint");
		exit(0);
	}
	game->cub.player_x = j - 1 + 0.5;
	game->cub.player_y = i - 1 + 0.5;
	game->player.rotation_angle = 0;
	game->player.dir_x = 1;
	game->player.dir_y = 0;
	game->player.plane_x = 0;
	game->player.plane_y = 0.66;
	playerflag = 1;
	return (playerflag);
}

int			divide(t_game *game, int i, int j, int playerflag)
{
	if (game->cub.bigmap[i][j] == '2')
		game->sprite_num++;
	else if (game->cub.bigmap[i][j] == 'N')
		playerflag = ft_n(game, playerflag, i, j);
	else if (game->cub.bigmap[i][j] == 'W')
		playerflag = ft_w(game, playerflag, i, j);
	else if (game->cub.bigmap[i][j] == 'S')
		playerflag = ft_s(game, playerflag, i, j);
	else if (game->cub.bigmap[i][j] == 'E')
		playerflag = ft_e(game, playerflag, i, j);
	else if (game->cub.map[i - 1][j - 1] != '0' &&\
			game->cub.map[i - 1][j - 1] != '1' &&\
			game->cub.map[i - 1][j - 1] != ' ')
		ft_error(0, -1, "Invalid map input");
	return (playerflag);
}
