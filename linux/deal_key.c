/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   deal_key.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stakabay <stakabay@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/03 11:24:12 by stakabay          #+#    #+#             */
/*   Updated: 2021/04/04 19:28:15 by stakabay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "constants.h"

void	move_right(t_game *game)
{
	if ((game->worldmap[(int)(game->posx + game->px *
		game->mspeed)][(int)(game->posy)]) == '0')
		game->posx += game->px * game->mspeed;
	if ((game->worldmap[(int)(game->posx)][(int)(game->posy +
		game->py * game->mspeed)]) == '0')
		game->posy += game->py * game->mspeed;
}

void	move_left(t_game *game)
{
	if ((game->worldmap[(int)(game->posx - game->px *
		game->mspeed)][(int)(game->posy)]) == '0')
		game->posx -= game->px * game->mspeed;
	if ((game->worldmap[(int)(game->posx)][(int)(game->posy -
		game->py * game->mspeed)]) == '0')
		game->posy -= game->py * game->mspeed;
}

void	move_front(t_game *game)
{
	if ((game->worldmap[(int)(game->posx + game->dirx *
		game->mspeed)][(int)(game->posy)]) == '0')
		game->posx += game->dirx * game->mspeed;
	if ((game->worldmap[(int)(game->posx)][(int)(game->posy +
		game->diry * game->mspeed)]) == '0')
		game->posy += game->diry * game->mspeed;
}

void	move_back(t_game *game)
{
	if ((game->worldmap[(int)(game->posx - game->dirx *
		game->mspeed)][(int)(game->posy)]) == '0')
		game->posx -= game->dirx * game->mspeed;
	if ((game->worldmap[(int)(game->posx)][(int)(game->posy -
		game->diry * game->mspeed)]) == '0')
		game->posy -= game->diry * game->mspeed;
}

int		deal_key(int key, t_game *game)
{
	if (key == K_W)
		move_front(game);
	if (key == K_S)
		move_back(game);
	if (key == K_D)
		move_right(game);
	if (key == K_A)
		move_left(game);
	if (key == K_L)
		rotate_left(game);
	if (key == K_R)
		rotate_right(game);
	if (key == K_ESC)
		exit(0);
	game->key_flag = 1;
	return (0);
}
