/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_elements.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stakabay <stakabay@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/17 10:59:38 by stakabay          #+#    #+#             */
/*   Updated: 2021/01/19 09:02:43 by stakabay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "readcub.h"

unsigned char	ft_r(t_game *game, char *line, int count, unsigned char rflag)
{
	char			**str;

	str = ft_split(line, ' ');
	count = 0;
	while (str[count] != NULL)
		count++;
	if (count != 3 || rflag & RFLAG)
		ft_error(0, -1, "invalid window size");
	game->cub.width = ft_atoi(str[1]);
	game->cub.height = ft_atoi(str[2]);
	if (game->cub.width <= 0 || game->cub.height <= 0)
		ft_error(0, -1, "invalid window size");
	rflag |= RFLAG;
	free(str);
	return (rflag);
}

unsigned int	ft_c(t_game *game, char *line, int count, unsigned char rflag)
{
	char			**str;

	line++;
	while (*line == ' ')
		line++;
	str = ft_split(line, ',');
	count = 0;
	while (str[count] != NULL)
		count++;
	if (count != 3 || rflag & CFLAG)
		ft_error(0, -1, "invalid ceiling RGB");
	game->cub.cr = ft_atoi(str[0]);
	game->cub.cg = ft_atoi(str[1]);
	game->cub.cb = ft_atoi(str[2]);
	if (game->cub.cr < 0 || 255 < game->cub.cr || game->cub.cg < 0 ||\
		255 < game->cub.cg || game->cub.cb < 0 || 255 < game->cub.cb)
		ft_error(0, -1, "RGB error");
	game->cub.ceilingcol = 0;
	game->cub.ceilingcol = (game->cub.cr << 16) +\
							(game->cub.cg << 8) + game->cub.cb;
	rflag |= CFLAG;
	free(str);
	return (rflag);
}

unsigned int	ft_f(t_game *game, char *line, int count, unsigned char rflag)
{
	char			**str;

	line++;
	while (*line == ' ')
		line++;
	str = ft_split(line, ',');
	count = 0;
	while (str[count] != NULL)
		count++;
	if (count != 3 || rflag & FFLAG)
		ft_error(0, -1, "invalid floor RGB");
	game->cub.fr = ft_atoi(str[0]);
	game->cub.fg = ft_atoi(str[1]);
	game->cub.fb = ft_atoi(str[2]);
	if (game->cub.fr < 0 || 255 < game->cub.fr || game->cub.fg < 0 ||\
		255 < game->cub.fg || game->cub.fb < 0 || 255 < game->cub.fb)
		ft_error(0, -1, "RGB error");
	game->cub.floorcol = 0;
	game->cub.floorcol = (game->cub.fr << 16) +\
						(game->cub.fg << 8) + game->cub.fb;
	rflag |= FFLAG;
	free(str);
	return (rflag);
}

void			elements_ot_map(t_game *game, int fd)
{
	char			*line;
	unsigned char	rflag;
	int				count;

	rflag = 0;
	count = 0;
	while (get_next_line(fd, &line) >= 0)
	{
		while (*line == ' ')
			line++;
		if (*line == 'R')
			rflag = ft_r(game, line, count, rflag);
		else if (*line == 'N' || *line == 'S' || *line == 'W' || *line == 'E')
			rflag = ft_compass(game, line, count, rflag);
		else if (*line == 'F')
			rflag = ft_f(game, line, count, rflag);
		else if (*line == 'C')
			rflag = ft_c(game, line, count, rflag);
		else if (rflag == 255)
			break ;
		else if (*line != '\0')
			ft_error(0, -1, ".cub text error");
	}
}
