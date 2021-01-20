/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   deal_key.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stakabay <stakabay@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/17 22:38:10 by stakabay          #+#    #+#             */
/*   Updated: 2021/01/17 22:55:31 by stakabay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "constants.h"

int			map_has_wall_at(t_game *game, float x, float y)
{
	int		map_grid_index_x;
	int		map_grid_index_y;

	if (x < 0 || x > COLS * TILE_SIZE || y < 0 || y > ROWS * TILE_SIZE)
		return (1);
	map_grid_index_x = floor(x / TILE_SIZE);
	map_grid_index_y = floor(y / TILE_SIZE);
	if (game->cub.map[map_grid_index_y][map_grid_index_x] == '1')
	{
		return (1);
	}
	else if (game->cub.map[map_grid_index_y][map_grid_index_x] == '2')
		return (2);
	return (0);
}

void		rotation_matrix(t_game *game)
{
	game->player.old_dir_x = game->player.dir_x;
	game->player.dir_x = game->player.dir_x * cos(game->player.turn_speed\
	* game->player.turn_direction) - game->player.dir_y * \
	sin(game->player.turn_speed * game->player.turn_direction);
	game->player.dir_y = game->player.old_dir_x * \
	sin(game->player.turn_speed * game->player.turn_direction) +\
	game->player.dir_y * cos(game->player.turn_speed *\
	game->player.turn_direction);
	game->player.old_plane_x = game->player.plane_x;
	game->player.plane_x = game->player.plane_x * \
	cos(game->player.turn_speed * game->player.turn_direction) -\
	game->player.plane_y * sin(game->player.turn_speed *\
	game->player.turn_direction);
	game->player.plane_y = game->player.old_plane_x * \
	sin(game->player.turn_speed * game->player.turn_direction) +\
	game->player.plane_y * cos(game->player.turn_speed *\
	game->player.turn_direction);
}

void		player_update(t_game *game)
{
	game->player.new_player_x = game->player.x + \
	cos(game->player.rotation_angle + (90 * PI / 180 \
	* game->player.lateralmove)) * game->player.walk_speed \
	* game->player.walk_direction;
	game->player.new_player_y = game->player.y + \
	sin(game->player.rotation_angle + (90 * PI / 180 \
	* game->player.lateralmove)) * game->player.walk_speed \
	* game->player.walk_direction;
	game->player.rotation_angle += game->player.turn_speed \
	* game->player.turn_direction;
	rotation_matrix(game);
	if (!map_has_wall_at(game, game->player.new_player_x,\
		game->player.new_player_y))
	{
		game->player.x = game->player.new_player_x;
		game->player.y = game->player.new_player_y;
		game->cub.player_x = game->player.x / TILE_SIZE;
		game->cub.player_y = game->player.y / TILE_SIZE;
	}
	game->player.walk_direction = 0;
	game->player.lateralmove = 0;
	game->player.turn_direction = 0;
}

int			deal_key(int key, t_game *game)
{
	if (key == KEY_ESC)
		exit(0);
	if (key == KEY_W || key == KEY_UP)
		game->player.walk_direction = 1;
	if (key == KEY_S || key == KEY_DOWN)
		game->player.walk_direction = -1;
	if (key == KEY_LEFT)
	{
		game->player.walk_direction = -1;
		game->player.lateralmove = 1;
	}
	if (key == KEY_RIGHT)
	{
		game->player.walk_direction = 1;
		game->player.lateralmove = 1;
	}
	if (key == KEY_D)
		game->player.turn_direction = 1;
	if (key == KEY_A)
		game->player.turn_direction = -1;
	player_update(game);
	game->player.g_key_flag = 1;
	return (0);
}
