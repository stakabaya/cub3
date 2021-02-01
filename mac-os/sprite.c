/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stakabay <stakabay@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/10 17:46:47 by stakabay          #+#    #+#             */
/*   Updated: 2021/01/30 21:17:24 by stakabay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "constants.h"
#define UDIV 1
#define VDIV 1
#define VMOVE 0.5

void	sprite_num_init(t_game *game, int i)
{
	float		vmove;

	game->sp_disc.sprite_x = game->sprite[i].x - game->cub.player_x;
	game->sp_disc.sprite_y = game->sprite[i].y - game->cub.player_y;
	game->sp_disc.inv_det = 1.0 / (game->player.plane_y * game->player.dir_x \
	- game->player.dir_y * game->player.plane_x);
	game->sp_disc.transform_x = game->sp_disc.inv_det * \
	(game->player.dir_x * game->sp_disc.sprite_y -\
	game->player.dir_y * game->sp_disc.sprite_x);
	game->sp_disc.transform_y = game->sp_disc.inv_det * \
	(-game->player.plane_x * game->sp_disc.sprite_y +\
	game->player.plane_y * game->sp_disc.sprite_x);
	game->sp_disc.sprite_screen_x = (int)((game->cub.width / 2) * \
	(1 + game->sp_disc.transform_x / game->sp_disc.transform_y));
	if ((game->cub.width - game->cub.height) > 200)
		vmove = 200;
	else if ((game->cub.width - game->cub.height) < -200)
		vmove = -10.0;
	else
		vmove = 0.0;
	game->sp_disc.v_move_screen = (int)(vmove / game->sp_disc.transform_y);
	game->sp_disc.sprite_height = \
	labs((long)(game->cub.height / (game->sp_disc.transform_y))) / VDIV;
	game->sp_disc.draw_start_y = -game->sp_disc.sprite_height /\
	2 + game->cub.height / 2 + game->sp_disc.v_move_screen;
}

void	set_sprite_nums(t_game *game, int i)
{
	sprite_num_init(game, i);
	if (game->sp_disc.draw_start_y < 0)
		game->sp_disc.draw_start_y = 0;
	game->sp_disc.draw_end_y = game->sp_disc.sprite_height /\
	2 + game->cub.height / 2 + game->sp_disc.v_move_screen;
	if (game->sp_disc.draw_end_y >= game->cub.height)
		game->sp_disc.draw_end_y = game->cub.height - 1;
	game->sp_disc.sprite_width = \
	(long)fabs((game->cub.height / game->sp_disc.transform_y) / UDIV);
	game->sp_disc.draw_start_x = \
	-game->sp_disc.sprite_width / 2 + game->sp_disc.sprite_screen_x;
	if (game->sp_disc.draw_start_x < 0)
		game->sp_disc.draw_start_x = 0;
	game->sp_disc.draw_end_x = \
	game->sp_disc.sprite_width / 2 + game->sp_disc.sprite_screen_x;
	if (game->sp_disc.draw_end_x >= game->cub.width)
		game->sp_disc.draw_end_x = game->cub.width - 1;
	game->sp_disc.stripe = game->sp_disc.draw_start_x;
}

void	draw_pixel(t_game *game)
{
	while (game->sp_disc.y < game->sp_disc.draw_end_y)
	{
		game->sp_disc.d = \
		(game->sp_disc.y - game->sp_disc.v_move_screen) * 256 - \
		game->cub.height * 128 + game->sp_disc.sprite_height * 128;
		game->sp_disc.tex_y = ((game->sp_disc.d * TILE_SIZE) / \
		game->sp_disc.sprite_height) / 256;
		game->sp_disc.color = game->texture[4].data\
		[TILE_SIZE * game->sp_disc.tex_y + game->sp_disc.tex_x];
		if ((game->sp_disc.color & 0x00FFFFFF) != 0)
			game->img.data[(game->sp_disc.y * game->cub.width) + \
			game->sp_disc.stripe] = game->sp_disc.color;
		game->sp_disc.y++;
	}
}

void	draw_sprite(t_game *game)
{
	while (game->sp_disc.stripe < game->sp_disc.draw_end_x)
	{
		game->sp_disc.tex_x = (long)((256 * (game->sp_disc.stripe - \
		(-game->sp_disc.sprite_width / 2 + game->sp_disc.sprite_screen_x)) * \
		TILE_SIZE / game->sp_disc.sprite_width) / 256);
		if (game->sp_disc.transform_y > 0 && game->sp_disc.stripe > 0 && \
		game->sp_disc.stripe < game->cub.width && \
		game->sp_disc.transform_y < game->z_buffer[game->sp_disc.stripe])
		{
			game->sp_disc.y = game->sp_disc.draw_start_y;
			draw_pixel(game);
		}
		game->sp_disc.stripe++;
	}
}

void	project_sprite(t_game *game)
{
	int			i;

	sort_sprite(game);
	i = 0;
	while (i < game->sprite_num)
	{
		set_sprite_nums(game, i);
		draw_sprite(game);
		i++;
	}
}
