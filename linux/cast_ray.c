/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cast_ray.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stakabay <stakabay@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/03 11:23:49 by stakabay          #+#    #+#             */
/*   Updated: 2021/04/03 19:06:37 by stakabay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "constants.h"

void	ca_direction(t_game *game)
{
	game->ct.mapx = (int)game->posx;
	game->ct.mapy = (int)game->posy;
	if (game->ct.rdiry == 0)
		game->ct.dx = 0;
	else if (game->ct.rdirx == 0)
		game->ct.dx = 1;
	else
		game->ct.dx = fabs(1 / game->ct.rdirx);
	if (game->ct.rdirx == 0)
		game->ct.dy = 0;
	else if (game->ct.rdiry == 0)
		game->ct.dy = 1;
	else
		game->ct.dy = fabs(1 / game->ct.rdiry);
}

void	ca_direction2(t_game *game)
{
	if (game->ct.rdirx < 0)
	{
		game->ct.stepx = -1;
		game->ct.sdistx = (game->posx - game->ct.mapx) * game->ct.dx;
	}
	else
	{
		game->ct.stepx = 1;
		game->ct.sdistx = (game->ct.mapx + 1.0 - game->posx) * game->ct.dx;
	}
	if (game->ct.rdiry < 0)
	{
		game->ct.stepy = -1;
		game->ct.sdisty = (game->posy - game->ct.mapy) * game->ct.dy;
	}
	else
	{
		game->ct.stepy = 1;
		game->ct.sdisty = (game->ct.mapy + 1.0 - game->posy) * game->ct.dy;
	}
}

void	hit_dir(t_game *game, int *side)
{
	game->hit = 0;
	while (game->hit == 0)
	{
		if (game->ct.sdistx < game->ct.sdisty)
		{
			game->ct.sdistx += game->ct.dx;
			game->ct.mapx += game->ct.stepx;
			*side = 0;
		}
		else
		{
			game->ct.sdisty += game->ct.dy;
			game->ct.mapy += game->ct.stepy;
			*side = 1;
		}
		if (game->worldmap[game->ct.mapx][game->ct.mapy] == '1')
			game->hit = 1;
	}
	if (*side == 0)
		game->ct.pwdist = (game->ct.mapx - game->posx +
		(1 - game->ct.stepx) / 2) / game->ct.rdirx;
	else
		game->ct.pwdist = (game->ct.mapy - game->posy
		+ (1 - game->ct.stepy) / 2) / game->ct.rdiry;
}

void	draw_ready(t_game *game, int *side, int *texn)
{
	game->ct.dstart = -game->ct.lheight / 2 + game->height / 2;
	if (game->ct.dstart < 0)
		game->ct.dstart = 0;
	game->ct.dend = game->ct.lheight / 2 + game->height / 2;
	if (game->ct.dend >= game->height)
		game->ct.dend = game->height - 1;
	if (*side == 1 && game->ct.rdiry > 0)
		*texn = 3;
	if (*side == 1 && game->ct.rdiry <= 0)
		*texn = 2;
	if (*side == 0 && game->ct.rdirx <= 0)
		*texn = 0;
	if (*side == 0 && game->ct.rdirx > 0)
		*texn = 1;
	if (*side == 0)
		game->ct.wallx = game->posy + game->ct.pwdist * game->ct.rdiry;
	else
		game->ct.wallx = game->posx + game->ct.pwdist * game->ct.rdirx;
	game->ct.wallx -= floor(game->ct.wallx);
}

void	cast_ray(t_game *game)
{
	int		side;
	int		x;

	x = 0;
	while (x < game->width)
	{
		game->ct.cx = 2 * x / (double)game->width - 1;
		game->ct.rdirx = game->dirx + game->px * game->ct.cx;
		game->ct.rdiry = game->diry + game->py * game->ct.cx;
		ca_direction(game);
		ca_direction2(game);
		hit_dir(game, &side);
		game->ct.lheight = (int)(game->height / game->ct.pwdist);
		draw_ready(game, &side, &(game->texn));
		game->ct.texx = (int)(game->ct.wallx * (double)TEXWIDTH);
		if (side == 0 && game->ct.rdirx > 0)
			game->ct.texx = TEXWIDTH - game->ct.texx - 1;
		if (side == 1 && game->ct.rdiry < 0)
			game->ct.texx = TEXWIDTH - game->ct.texx - 1;
		game->step = 1.0 * TEXHEIGHT / game->ct.lheight;
		game->ct.texpos = (game->ct.dstart - game->height /
		2 + game->ct.lheight / 2) * game->step;
		set_color(game, &x, &(game->texn), &side);
		game->zbuf[x++] = game->ct.pwdist;
	}
}
