/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stakabay <stakabay@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/17 23:38:57 by stakabay          #+#    #+#             */
/*   Updated: 2021/01/17 23:55:58 by stakabay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "constants.h"

void		draw_map_wall(t_game *game, int i, int j)
{
	int		k;
	int		m;
	int		tile_x;
	int		tile_y;

	tile_x = j * (int)TILE_SIZE * MINIMAP_SCALE_FACTOR;
	tile_y = i * ((int)TILE_SIZE * MINIMAP_SCALE_FACTOR);
	k = 0;
	while (k < ((int)TILE_SIZE * MINIMAP_SCALE_FACTOR))
	{
		m = 0;
		while (m < ((int)TILE_SIZE * MINIMAP_SCALE_FACTOR))
		{
			game->img.data[(tile_y + k) * \
			game->cub.width + tile_x + m] = 0xFFFFFF;
			m++;
		}
		k++;
	}
}

void		render_map(t_game *game)
{
	int		i;
	int		j;

	i = 0;
	while (i < game->cub.rows)
	{
		j = 0;
		while (j < game->cub.cols)
		{
			if (game->cub.map[i][j] == '1')
				draw_map_wall(game, i, j);
			j++;
		}
		i++;
	}
}

void		render_rays(t_game *game)
{
	int		i;
	float	cos_ang;
	float	sin_ang;
	int		k;

	k = 0;
	while (k < game->num_rays)
	{
		cos_ang = cos(game->rays[k].ray_angle);
		sin_ang = sin(game->rays[k].ray_angle);
		i = 0;
		while (i < (game->rays[k].distance * MINIMAP_SCALE_FACTOR))
		{
			game->img.data[(int)((game->player.y * MINIMAP_SCALE_FACTOR) +\
			(sin_ang * i)) * game->cub.width + (int)((game->player.x * \
			MINIMAP_SCALE_FACTOR) + (cos_ang * i))] = 0x00FF0000;
			i++;
		}
		k++;
	}
}

void		render_player(t_game *game)
{
	float	i;
	float	j;
	float	cos_ang;
	float	sin_ang;

	cos_ang = cos(game->player.rotation_angle);
	sin_ang = sin(game->player.rotation_angle);
	i = 0;
	j = 0;
	while (i <= 20)
	{
		if (((game->player.y * MINIMAP_SCALE_FACTOR) + (sin_ang * i)) > 0 && \
				((game->player.x * MINIMAP_SCALE_FACTOR) + (cos_ang * i) > 0))
			game->img.data[(int)((game->player.y * MINIMAP_SCALE_FACTOR) + \
			(sin_ang * i)) * game->cub.width + \
			(int)((game->player.x * MINIMAP_SCALE_FACTOR) + \
			(cos_ang * i))] = 0x00FFFFFF;
		i++;
	}
}
