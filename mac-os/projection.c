/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   projection.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stakabay <stakabay@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/18 21:54:29 by stakabay          #+#    #+#             */
/*   Updated: 2021/01/30 21:10:52 by stakabay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "constants.h"

void	ceiling_and_floor(t_game *game, int top_px, int bottom_px, int i)
{
	int		y;

	y = 0;
	while (y < top_px)
	{
		game->img.data[(y * game->cub.width) + i] = game->cub.ceilingcol;
		y += 1;
	}
	y = bottom_px;
	while (y < game->cub.height)
	{
		game->img.data[(y * game->cub.width) + i] = game->cub.floorcol;
		y += 1;
	}
}

void	set_num(t_game *game, int x)
{
	game->proj.perp_dis = game->rays[x].distance * \
	cos(game->rays[x].ray_angle - game->player.rotation_angle);
	game->proj.proj_height = \
	(TILE_SIZE / game->proj.perp_dis) * game->proj.dis_proj_plane;
	game->proj.strip_height = (int)game->proj.proj_height;
	game->proj.top_pixel = \
	(game->cub.height / 2) - (game->proj.strip_height / 2);
	game->proj.top_pixel = \
	game->proj.top_pixel < 0 ? 0 : game->proj.top_pixel;
	game->proj.bottom_pixel = \
	(game->cub.height / 2) + (game->proj.strip_height / 2);
	game->proj.bottom_pixel =\
	game->proj.bottom_pixel > game->cub.height ? \
	game->cub.height : game->proj.bottom_pixel;
}

void	ft_ewsn(t_game *game, int x, int texnum)
{
	int		tex_width;
	int		tex_height;

	tex_width = game->texture[texnum].width;
	tex_height = game->texture[texnum].height;
	if (game->rays[x].is_ray_facing_up && \
	!(game->rays[x].was_hit_vertical))
		game->proj.texel_color = game->texture[0].data\
		[(tex_width * game->proj.tex_offset_y) + game->proj.tex_offset_x];
	else if (game->rays[x].is_ray_facing_down && \
			!(game->rays[x].was_hit_vertical))
		game->proj.texel_color = game->texture[1].data\
		[(tex_width * game->proj.tex_offset_y) \
		+ (tex_width - game->proj.tex_offset_x - 1)];
	else if (game->rays[x].is_ray_facing_left && game->rays[x].was_hit_vertical)
		game->proj.texel_color = game->texture[2].data[(tex_width * game->proj.\
		tex_offset_y) + (tex_width - game->proj.tex_offset_x - 1)];
	else if (game->rays[x].is_ray_facing_right && \
			game->rays[x].was_hit_vertical)
		game->proj.texel_color = game->texture[3].data\
		[(tex_width * game->proj.tex_offset_y) + game->proj.tex_offset_x];
	else
		game->proj.texel_color = \
		game->texture[game->rays[x].wall_hit_content - 1].data\
		[(tex_width * game->proj.tex_offset_y) + game->proj.tex_offset_x];
}

void	project_wall(t_game *game, int x)
{
	int		y;
	int		texnum;

	y = game->proj.top_pixel;
	while (y < game->proj.bottom_pixel)
	{
		texnum = game->rays[x].wall_hit_content - 1;
		if (game->rays[x].was_hit_vertical)
			game->proj.tex_offset_x = \
			(int)game->rays[x].wall_hit_y % game->texture[texnum].width;
		else
			game->proj.tex_offset_x = \
			(int)game->rays[x].wall_hit_x % game->texture[texnum].width;
		game->proj.distance_from_top = \
		y + (game->proj.strip_height / 2) - (game->cub.height / 2);
		game->proj.tex_offset_y = game->proj.distance_from_top * \
		((float)game->texture[texnum].height / game->proj.strip_height);
		ft_ewsn(game, x, texnum);
		game->img.data[(y * game->cub.width) + x] = game->proj.texel_color;
		y += 1;
	}
}

void	generate_3d_projection(t_game *game)
{
	int		x;

	x = 0;
	while (x < game->num_rays)
	{
		set_num(game, x);
		project_wall(game, x);
		ceiling_and_floor(game, game->proj.top_pixel, \
							game->proj.bottom_pixel, x);
		x++;
	}
}
