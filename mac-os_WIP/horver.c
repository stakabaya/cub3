/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   horver.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stakabay <stakabay@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/17 23:05:22 by stakabay          #+#    #+#             */
/*   Updated: 2021/01/17 23:23:56 by stakabay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "constants.h"

void	set_ray_dic(float horz_hit, float vert_hit, int id, t_game *game)
{
	if (vert_hit < horz_hit)
	{
		game->rays[id].distance = vert_hit;
		game->rays[id].wall_hit_x = game->horzvert.vert_wall_hit_x;
		game->rays[id].wall_hit_y = game->horzvert.vert_wall_hit_y;
		game->rays[id].wall_hit_content = game->horzvert.vert_wall_content;
		game->rays[id].was_hit_vertical = TRUE;
	}
	else
	{
		game->rays[id].distance = horz_hit;
		game->rays[id].wall_hit_x = game->horzvert.horz_wall_hit_x;
		game->rays[id].wall_hit_y = game->horzvert.horz_wall_hit_y;
		game->rays[id].wall_hit_content = game->horzvert.horz_wall_content;
		game->rays[id].was_hit_vertical = FALSE;
	}
	game->z_buffer[id] = game->rays[id].distance / TILE_SIZE;
	game->rays[id].is_ray_facing_down = game->ray_prop.is_ray_facing_down;
	game->rays[id].is_ray_facing_up = game->ray_prop.is_ray_facing_up;
	game->rays[id].is_ray_facing_right = game->ray_prop.is_ray_facing_right;
	game->rays[id].is_ray_facing_left = game->ray_prop.is_ray_facing_left;
}

void	serch_vert_wall(t_game *game, float n_vert_x, float n_vert_y)
{
	float	x_to_check;
	float	y_to_check;

	while (n_vert_x >= 0 && n_vert_x <= COLS * TILE_SIZE &&\
		n_vert_y >= 0 && n_vert_y <= ROWS * TILE_SIZE)
	{
		x_to_check = n_vert_x + \
		(game->ray_prop.is_ray_facing_left ? -1 : 0);
		y_to_check = n_vert_y;
		if (map_has_wall_at(game, x_to_check, y_to_check) == 1)
		{
			game->horzvert.vert_wall_hit_x = n_vert_x;
			game->horzvert.vert_wall_hit_y = n_vert_y;
			game->horzvert.vert_wall_content = 1;
			game->horzvert.found_vert_wall_hit = TRUE;
			break ;
		}
		n_vert_x += game->ray_prop.xstep;
		n_vert_y += game->ray_prop.ystep;
	}
}

void	vert_ray_grid_intersetion(float ray_angle, t_game *game)
{
	float n_vert_x;
	float n_vert_y;

	game->horzvert.found_vert_wall_hit = FALSE;
	game->horzvert.vert_wall_hit_x = 0;
	game->horzvert.vert_wall_hit_y = 0;
	game->horzvert.vert_wall_content = 0;
	game->ray_prop.xintercept = floor(game->player.x / TILE_SIZE) * TILE_SIZE;
	game->ray_prop.xintercept += game->ray_prop.is_ray_facing_right ?\
	TILE_SIZE : 0;
	game->ray_prop.yintercept = game->player.y + \
	(game->ray_prop.xintercept - game->player.x) * tan(ray_angle);
	game->ray_prop.xstep = TILE_SIZE;
	game->ray_prop.xstep *= game->ray_prop.is_ray_facing_left ? -1 : 1;
	game->ray_prop.ystep = TILE_SIZE * tan(ray_angle);
	game->ray_prop.ystep *= \
	(game->ray_prop.is_ray_facing_up && game->ray_prop.ystep > 0) ? -1 : 1;
	game->ray_prop.ystep *= \
	(game->ray_prop.is_ray_facing_down && game->ray_prop.ystep < 0) ? -1 : 1;
	n_vert_x = game->ray_prop.xintercept;
	n_vert_y = game->ray_prop.yintercept;
	serch_vert_wall(game, n_vert_x, n_vert_y);
}

void	serch_hor_wall(t_game *game, float n_horz_x, float n_horz_y)
{
	float	x_to_check;
	float	y_to_check;

	while (n_horz_x >= 0 && n_horz_x <= COLS * TILE_SIZE &&\
		n_horz_y >= 0 && n_horz_y <= ROWS * TILE_SIZE)
	{
		x_to_check = n_horz_x;
		y_to_check = n_horz_y + (game->ray_prop.is_ray_facing_up ? -1 : 0);
		if (map_has_wall_at(game, x_to_check, y_to_check) == 1)
		{
			game->horzvert.horz_wall_hit_x = n_horz_x;
			game->horzvert.horz_wall_hit_y = n_horz_y;
			game->horzvert.horz_wall_content = 1;
			game->horzvert.found_horz_wall_hit = TRUE;
			break ;
		}
		n_horz_x += game->ray_prop.xstep;
		n_horz_y += game->ray_prop.ystep;
	}
}

void	hor_ray_grid_intersetion(float ray_angle, t_game *game)
{
	float	n_horz_x;
	float	n_horz_y;

	game->horzvert.found_horz_wall_hit = FALSE;
	game->horzvert.horz_wall_hit_x = 0;
	game->horzvert.horz_wall_hit_y = 0;
	game->horzvert.horz_wall_content = 0;
	game->ray_prop.yintercept = \
	floor(game->player.y / TILE_SIZE) * TILE_SIZE;
	game->ray_prop.yintercept += \
	game->ray_prop.is_ray_facing_down ? TILE_SIZE : 0;
	game->ray_prop.xintercept = game->player.x + \
	(game->ray_prop.yintercept - game->player.y) / tan(ray_angle);
	game->ray_prop.ystep = TILE_SIZE;
	game->ray_prop.ystep *= game->ray_prop.is_ray_facing_up ? -1 : 1;
	game->ray_prop.xstep = TILE_SIZE / tan(ray_angle);
	game->ray_prop.xstep *= \
	(game->ray_prop.is_ray_facing_left && game->ray_prop.xstep > 0) ? -1 : 1;
	game->ray_prop.xstep *= \
	(game->ray_prop.is_ray_facing_right && game->ray_prop.xstep < 0) ? -1 : 1;
	n_horz_x = game->ray_prop.xintercept;
	n_horz_y = game->ray_prop.yintercept;
	serch_hor_wall(game, n_horz_x, n_horz_y);
}
