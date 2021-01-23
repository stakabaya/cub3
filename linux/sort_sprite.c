/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_sprite.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stakabay <stakabay@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/17 12:20:54 by stakabay          #+#    #+#             */
/*   Updated: 2021/01/17 12:26:41 by stakabay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "constants.h"

void			ft_swap(t_game *game, int i, int j)
{
	t_sprite	*tmp;

	tmp = NULL;
	if ((tmp = malloc(sizeof(t_sprite))) == NULL)
		exit(1);
	tmp->sprite_distance = game->sprite[i].sprite_distance;
	game->sprite[i].sprite_distance = game->sprite[j].sprite_distance;
	game->sprite[j].sprite_distance = tmp->sprite_distance;
	tmp->x = game->sprite[i].x;
	game->sprite[i].x = game->sprite[j].x;
	game->sprite[j].x = tmp->x;
	tmp->y = game->sprite[i].y;
	game->sprite[i].y = game->sprite[j].y;
	game->sprite[j].y = tmp->y;
	free(tmp);
}

void			ft_sort(t_game *game)
{
	int			i;
	int			j;

	i = 0;
	while (i < game->sprite_num - 1)
	{
		j = i + 1;
		while (j < game->sprite_num)
		{
			if (game->sprite[i].sprite_distance <\
				game->sprite[j].sprite_distance)
				ft_swap(game, i, j);
			j++;
		}
		i++;
	}
}

void			sort_sprite(t_game *game)
{
	int			i;

	i = 0;
	while (i < game->sprite_num)
	{
		game->sprite[i].sprite_distance = \
		((game->cub.player_x - game->sprite[i].x) *\
		(game->cub.player_x - game->sprite[i].x) +\
		(game->cub.player_y - game->sprite[i].y) *\
		(game->cub.player_y - game->sprite[i].y));
		i++;
	}
	ft_sort(game);
}
