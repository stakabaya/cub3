/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readcub.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stakabay <stakabay@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/17 12:17:57 by stakabay          #+#    #+#             */
/*   Updated: 2021/01/17 12:18:00 by stakabay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef READCUB_H
# define READCUB_H

# include <errno.h>
# include "../constants.h"

# define RFLAG 1
# define NOFLAG 2
# define SOFLAG 4
# define WEFLAG 8
# define EAFLAG 16
# define SFLAG 32
# define FFLAG 64
# define CFLAG 128

void			elements_ot_map(t_game *game, int fd);
unsigned char	ft_compass(t_game *game, char *line,\
							int count, unsigned char rflag);
void			set_sprite(t_game *game);
void			make_map(t_game *game, int fd);
void			make_bigmap(t_game *game);
void			set_map(t_game *game);
int				divide(t_game *game, int i, int j, int playerflag);

#endif
