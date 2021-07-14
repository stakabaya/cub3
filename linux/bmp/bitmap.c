/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bitmap.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stakabay <stakabay@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/03 17:56:35 by stakabay          #+#    #+#             */
/*   Updated: 2021/04/03 17:56:42 by stakabay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bitmap.h"

void	zero_pad(int fd, int pad)
{
	unsigned char	zero[3];

	ft_bzero(zero, 3);
	if (pad > 0)
		write(fd, &zero, pad);
}

void	write_header(int fd, t_game *game)
{
	unsigned char	buf[54];
	unsigned int	file_size;

	file_size = DEFAULT_HEADER_SIZE + game->width * 4 * game->height;
	ft_bzero(buf, 54);
	buf[0] = (unsigned char)'B';
	buf[1] = (unsigned char)'M';
	ft_memcpy(buf + 2, &file_size, sizeof(file_size));
	buf[10] = (unsigned char)54;
	buf[14] = (unsigned char)40;
	ft_memcpy(buf + 18, &game->width, sizeof(game->width));
	ft_memcpy(buf + 22, &game->height, sizeof(game->height));
	buf[26] = (unsigned char)1;
	buf[28] = (unsigned char)32;
	write(fd, buf, 54);
}

void	write_bmp(int fd, t_game *game)
{
	int				x;
	unsigned char	*buf;
	int				stride;

	x = game->height - 1;
	while (x >= 0)
	{
		buf = (unsigned char *)game->buf[x];
		stride = game->width * 4;
		write(fd, buf, stride);
		--x;
	}
}

void	get_bit(t_game *game)
{
	int		fd;

	fd = open("./bitmap.bmp", O_CREAT | O_WRONLY | O_TRUNC, S_IRWXU);
	if (fd == -1)
		put_error("Error\nmiss open");
	write_header(fd, game);
	write_bmp(fd, game);
	close(fd);
}
