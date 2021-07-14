/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bitmap.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stakabay <stakabay@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/18 09:38:54 by stakabay          #+#    #+#             */
/*   Updated: 2021/01/18 09:44:23 by stakabay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bitmap.h"

void				safe_free(uint8_t *buffer, const char *str)
{
	int				len;

	len = ft_strlen(str);
	if (buffer != NULL)
	{
		free(buffer);
		buffer = NULL;
	}
	write(1, str, len);
	exit(0);
}

void				ft_init(t_fileheader *file, t_infoheader *info,\
							int stride, t_game *game)
{
	file->bf_type = FILE_TYPE;
	file->bf_size = DEFAULT_HEADER_SIZE + stride * game->cub.height;
	file->bf_reserved1 = 0;
	file->bf_reserved2 = 0;
	file->bf_off_bits = DEFAULT_HEADER_SIZE;
	info->bi_size = INFO_HEADER_SIZE;
	info->bi_width = game->cub.width;
	info->bi_height = game->cub.height;
	info->bi_planes = 1;
	info->bi_bit_count = 24;
	info->bi_compression = 0;
	info->bi_sizeimage = stride * game->cub.height;
	info->bi_xpels_per_meter = 0;
	info->bi_ypels_per_meter = 0;
	info->bi_cr_used = 0;
	info->bi_clr_important = 0;
}

void				make_bmp(t_game *game, int stride, uint8_t **buffer, int fp)
{
	int				x;
	int				y;
	uint8_t			*row;

	y = game->cub.height - 1;
	while (y >= 0)
	{
		row = *buffer;
		x = 0;
		while (x < game->cub.width)
		{
			*row++ = (game->img.data[(y * game->cub.width) + x] & 255);
			*row++ = ((game->img.data[(y * game->cub.width) + x] >> 8) & 255);
			*row++ = ((game->img.data[(y * game->cub.width) + x] >> 16) & 255);
			x++;
		}
		if (write(fp, *buffer, stride) == -1)
			safe_free(*buffer, "bmp error");
		y--;
	}
}

void				write_bmp_simple_stream(int fp, t_game *game)
{
	uint8_t			header_buffer[DEFAULT_HEADER_SIZE];
	t_fileheader	*file;
	t_infoheader	*info;
	int				stride;
	uint8_t			*buffer;

	file = (t_fileheader*)header_buffer;
	info = (t_infoheader*)(header_buffer + FILE_HEADER_SIZE);
	stride = (game->cub.width * 3 + 3) / 4 * 4;
	if ((buffer = malloc(stride)) == NULL)
		safe_free(NULL, "bmp error");
	ft_init(file, info, stride, game);
	if (write(fp, header_buffer, DEFAULT_HEADER_SIZE) == -1)
		safe_free(buffer, "bmp error");
	ft_memset(buffer, 0, stride);
	make_bmp(game, stride, &buffer, fp);
	free(buffer);
}

void				write_bmp_simple_file(const char *filename, t_game *game)
{
	int				fp;

	fp = open(filename, O_WRONLY | O_CREAT);
	if (fp == -1)
		safe_free(NULL, filename);
	write_bmp_simple_stream(fp, game);
	close(fp);
}
