/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stakabay <stakabay@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/17 22:21:06 by stakabay          #+#    #+#             */
/*   Updated: 2021/01/17 22:36:25 by stakabay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "constants.h"

int			txture_init(t_game *game, int i)
{
	char	*str;
	int		len;

	if (i == 0)
		str = game->cub.nopath;
	else if (i == 1)
		str = game->cub.sopath;
	else if (i == 2)
		str = game->cub.wepath;
	else if (i == 3)
		str = game->cub.eapath;
	else if (i == 4)
		str = game->cub.sppath;
	else
		str = game->cub.nopath;
	len = ft_strlen(str);
	if (ft_memcmp((str + (len - 4)), ".xpm", 4) != 0 && \
		ft_memcmp((str + (len - 4)), ".png", 4) != 0)
		ft_error(0, 0, "unsupported texture extention");
	if (!(game->texture[i].img = mlx_xpm_file_to_image(game->mlx, \
		str, &game->texture[i].width, &game->texture[i].height)))
		ft_error(0, 0, "readerror");
	game->texture[i].data = (int *)mlx_get_data_addr(game->texture[i].img, \
	&game->texture[i].bpp, &game->texture[i].size_l, &game->texture[i].endian);
	return (1);
}

void		player_init(t_game *game)
{
	game->player.x = game->cub.player_x * TILE_SIZE;
	game->player.y = game->cub.player_y * TILE_SIZE;
	game->player.width = 1;
	game->player.height = 1;
	game->player.turn_direction = 0;
	game->player.walk_direction = 0;
	game->player.walk_speed = 10;
	game->player.turn_speed = 5 * (PI / 180);
	game->player.lateralmove = 0;
}

void		window_init(t_game *game)
{
	int		sizex;
	int		sizey;

	mlx_get_screen_size(game->mlx, &sizex, &sizey);
	if (game->cub.width > sizex)
		game->cub.width = sizex;
	if (game->cub.height > sizey)
		game->cub.height = sizey;
	game->mlx = mlx_init();
	game->win = mlx_new_window(game->mlx, \
				game->cub.width, game->cub.height, "mlx 42");
}

void		img_init(t_game *game)
{
	game->img.img = mlx_new_image(game->mlx, game->cub.width, game->cub.height);
	game->img.data = (int *)mlx_get_data_addr(game->img.img, \
	&game->img.bpp, &game->img.size_l, &game->img.endian);
}

int			init(t_game *game, char **argv, int argc)
{
	int		i;

	i = 0;
	if (readcubtxt(game, argv, argc) == -1)
		return (0);
	window_init(game);
	game->num_rays = game->cub.width;
	game->texture = malloc(sizeof(t_texture) * NUM_TEXTURE);
	game->sprite_ray = malloc(sizeof(t_sprite_ray) * game->cub.width);
	game->z_buffer = malloc(sizeof(double) * game->cub.width);
	img_init(game);
	player_init(game);
	game->player.g_key_flag = 1;
	while (i < NUM_TEXTURE)
	{
		if (txture_init(game, i) == 0)
			return (0);
		i++;
	}
	return (1);
}
