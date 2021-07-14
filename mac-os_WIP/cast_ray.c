/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cast_ray.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stakabay <stakabay@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/17 23:02:08 by stakabay          #+#    #+#             */
/*   Updated: 2021/01/18 21:53:55 by stakabay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "constants.h"

float	distance_between_points(float x1, float y1, float x2, float y2)
{
	return (sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1)));
}

void	ray_facing_dir(t_game *game, float ray_angle)
{
	game->ray_prop.is_ray_facing_down = ray_angle > 0 && ray_angle < PI;
	game->ray_prop.is_ray_facing_up = !game->ray_prop.is_ray_facing_down;
	game->ray_prop.is_ray_facing_right = \
	ray_angle < 0.5 * PI || ray_angle > 1.5 * PI;
	game->ray_prop.is_ray_facing_left = !game->ray_prop.is_ray_facing_right;
}

float	normalize_angle(float angle)
{
	angle = remainder(angle, TWO_PI);
	if (angle < 0)
		angle = TWO_PI + angle;
	return (angle);
}

void	cast_ray(float ray_angle, int id, t_game *game)
{
	float	horz_hit;
	float	vert_hit;

	ray_angle = normalize_angle(ray_angle);
	game->rays[id].ray_angle = ray_angle;
	ray_facing_dir(game, ray_angle);
	hor_ray_grid_intersetion(ray_angle, game);
	vert_ray_grid_intersetion(ray_angle, game);
	horz_hit = game->horzvert.found_horz_wall_hit ? \
	distance_between_points(game->player.x, game->player.y, \
	game->horzvert.horz_wall_hit_x, \
	game->horzvert.horz_wall_hit_y) : FLT_MAX;
	vert_hit = game->horzvert.found_vert_wall_hit ? \
	distance_between_points(game->player.x, game->player.y, \
	game->horzvert.vert_wall_hit_x, \
	game->horzvert.vert_wall_hit_y) : FLT_MAX;
	set_ray_dic(horz_hit, vert_hit, id, game);
}

void	cast_all_rays(t_game *game)
{
	float	ray_angle;
	int		col;

	game->rays = malloc(sizeof(t_ray) * game->cub.width);
	game->proj.dis_proj_plane = \
	(game->cub.width / 2) / tan(FOV_ANGLE / 2);
	col = 0;
	while (col < game->num_rays)
	{
		ray_angle = game->player.rotation_angle + \
		atan((col - game->num_rays / 2) / \
		game->proj.dis_proj_plane);
		cast_ray(ray_angle, col, game);
		col++;
	}
}
