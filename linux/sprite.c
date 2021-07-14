/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stakabay <stakabay@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/03 11:24:49 by stakabay          #+#    #+#             */
/*   Updated: 2021/04/03 19:07:36 by stakabay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "constants.h"

void	set_sprite(t_game *game, int *i)
{
	game->cs.spritex = game->sprite[game->sorder[*i]].x - game->posx;
	game->cs.spritey = game->sprite[game->sorder[*i]].y - game->posy;
	game->cs.invdet = 1.0 / (game->px * game->diry - game->dirx * game->py);
	game->cs.tx = game->cs.invdet * (game->diry *
	game->cs.spritex - game->dirx * game->cs.spritey);
	game->cs.ty = game->cs.invdet * (-game->py *
	game->cs.spritex + game->px * game->cs.spritey);
	game->cs.sx = (int)((game->width / 2) * (1 + game->cs.tx / game->cs.ty));
	game->cs.ms = (int)(VMOVE / game->cs.ty);
	game->cs.sh = (int)fabs((game->height / game->cs.ty) / VDIV);
	game->cs.dstarty = -game->cs.sh / 2 + game->height / 2 + game->cs.ms;
	if (game->cs.dstarty < 0)
		game->cs.dstarty = 0;
	game->cs.dendy = game->cs.sh / 2 + game->height / 2 + game->cs.ms;
	if (game->cs.dendy >= game->height)
		game->cs.dendy = game->height - 1;
	game->cs.swidth = (int)fabs((game->height / game->cs.ty) / UDIV);
	game->cs.dstartx = -game->cs.swidth / 2 + game->cs.sx;
	if (game->cs.dstartx < 0)
		game->cs.dstartx = 0;
	game->cs.dendx = game->cs.swidth / 2 + game->cs.sx;
	if (game->cs.dendx >= game->width)
		game->cs.dendx = game->width - 1;
}

void	sprite_color(t_game *game)
{
	int		y;

	game->stripe = game->cs.dstartx;
	while (game->stripe < game->cs.dendx)
	{
		game->cs.texx = (int)((256 * (game->stripe - (-game->cs.swidth / 2 +
		game->cs.sx)) * TEXWIDTH / game->cs.swidth) / 256);
		if (game->cs.ty > 0 && game->stripe > 0 && game->stripe < game->width &&
		game->cs.ty < game->zbuf[game->stripe])
		{
			y = game->cs.dstarty;
			while (y < game->cs.dendy)
			{
				game->d = (y - game->cs.ms) * 256 - game->height *
				128 + game->cs.sh * 128;
				game->cs.texy = ((game->d * TEXHEIGHT) / game->cs.sh) / 256;
				game->color = game->texture[4][TEXWIDTH *
				game->cs.texy + game->cs.texx];
				if ((game->color & 0x00FFFFFF) != 0)
					game->buf[y][game->stripe] = game->color;
				y++;
			}
		}
		game->stripe++;
	}
}

void	sort_order(t_pair *orders, int amount)
{
	t_pair	tmp;
	int		i;
	int		j;

	i = 0;
	tmp.first = 0;
	tmp.second = 0;
	while (i < amount)
	{
		j = 0;
		while (j < amount - 1)
		{
			if (orders[j].first > orders[j + 1].first)
			{
				tmp.first = orders[j].first;
				tmp.second = orders[j].second;
				orders[j].first = orders[j + 1].first;
				orders[j].second = orders[j + 1].second;
				orders[j + 1].first = tmp.first;
				orders[j + 1].second = tmp.second;
			}
			j++;
		}
		i++;
	}
}

void	sort_sprites(int *order, double *dist, int amount)
{
	t_pair	*sprites;
	int		i;

	i = 0;
	if ((sprites = (t_pair*)malloc(sizeof(t_pair) * amount)) == NULL)
		exit(1);
	while (i < amount)
	{
		sprites[i].first = dist[i];
		sprites[i].second = order[i];
		i++;
	}
	sort_order(sprites, amount);
	i = 0;
	while (i < amount)
	{
		dist[i] = sprites[amount - i - 1].first;
		order[i] = sprites[amount - i - 1].second;
		i++;
	}
	free(sprites);
}

void	cast_sprite(t_game *game)
{
	int		i;

	i = 0;
	while (i < game->numsprites)
	{
		game->sorder[i] = i;
		game->sdis[i] = ((game->posx - game->sprite[i].x) *
		(game->posx - game->sprite[i].x) + (game->posy - game->sprite[i].y) *
		(game->posy - game->sprite[i].y));
		i++;
	}
	sort_sprites(game->sorder, game->sdis, game->numsprites);
	i = 0;
	while (i < game->numsprites)
	{
		set_sprite(game, &i);
		sprite_color(game);
		i++;
	}
}
