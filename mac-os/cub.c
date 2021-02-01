/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stakabay <stakabay@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/05 23:36:07 by stakabay          #+#    #+#             */
/*   Updated: 2021/01/30 21:13:03 by stakabay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "constants.h"

int			ft_error(int error_num, int return_num, char *error_str)
{
	errno = error_num;
	perror(error_str);
	exit(return_num);
}

int			ft_close(void)
{
	exit(0);
}

int			main_loop(t_game *game)
{
	if (game->player.g_key_flag == 1)
	{
		cast_all_rays(game);
		generate_3d_projection(game);
		project_sprite(game);
		render_map(game);
		render_rays(game);
		render_player(game);
		if (game->bmp == 1)
		{
			write_bmp_simple_file("cub.bmp", game);
			game->bmp = 0;
			ft_close();
		}
		mlx_put_image_to_window(game->mlx, game->win, game->img.img, 0, 0);
	}
	game->player.g_key_flag = 0;
	return (0);
}

int			main(int argc, char **argv)
{
	t_game		game;

	if (argc < 2 || 3 < argc)
		ft_error(0, 0, "too many arguments");
	if (!(init(&game, argv, argc)))
		ft_error(0, 0, "init error");
	main_loop(&game);
	mlx_hook(game.win, X_EVENT_KEY_EXIT, 1, &ft_close, NULL);
	mlx_hook(game.win, X_EVENT_KEY_PRESS, 1, &deal_key, &game);
	mlx_loop_hook(game.mlx, &main_loop, &game);
	mlx_loop(game.mlx);
}
