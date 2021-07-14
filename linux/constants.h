/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   constants.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stakabay <stakabay@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/03 11:25:29 by stakabay          #+#    #+#             */
/*   Updated: 2021/04/04 19:21:49 by stakabay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONSTANTS_H
# define CONSTANTS_H

# include "./libft/libft.h"
# include "GNL/get_next_line.h"
# include <math.h>
# include <string.h>
# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include <unistd.h>

# ifdef __linux__
#  include <X11/Xlib.h>
#  include <sys/ipc.h>
#  include <sys/shm.h>
#  include <X11/extensions/XShm.h>
#  include "./minilibx-linux/mlx.h"
#  define K_A 97
#  define K_S 115
#  define K_D 100
#  define K_W 119
#  define K_ESC 65307
#  define K_R 65363
#  define K_L 65361

# else
#  include "./minilibx_mms_20200219/mlx.h"
#  define K_A 0
#  define K_S 1
#  define K_D 2
#  define K_W 13
#  define K_ESC 53
#  define K_R 124
#  define K_L 123
# endif

# define X_EVENT_KEY_PRESS 2
# define X_EVENT_KEY_RELEASE 3
# define X_EVENT_KEY_EXIT 17
# define TEXWIDTH 64
# define TEXHEIGHT 64
# define BUFFER_SIZE 1000

# define RESOL 1
# define NORTH 2
# define SOUTH 4
# define WEST 8
# define EAST 16
# define SPRITE 32
# define FLOOR 64
# define CEIL 128
# define ALL 255

# define N 1
# define S 2
# define W 4
# define E 8

# define FILEHEADERSIZE 14
# define INFOHEADERSIZE 40
# define HEADERSIZE 54

# define UDIV 1
# define VDIV 1
# define VMOVE 0.0

typedef struct		s_image
{
	unsigned int	height;
	unsigned int	width;
	unsigned int	*color;
}					t_image;

int					get_next_line(int fd, char **line);

typedef struct		s_img
{
	void			*ptr;
	void			*img;
	int				*data;
	int				size_l;
	int				bpp;
	int				endian;
	int				img_width;
	int				img_height;
}					t_img;

typedef struct		s_sprite
{
	double			x;
	double			y;
}					t_sprite;

typedef struct		s_sp
{
	double			spritex;
	double			spritey;
	double			invdet;
	double			tx;
	double			ty;
	int				sx;
	int				ms;
	int				sh;
	int				dstarty;
	int				dendy;
	int				dendx;
	int				swidth;
	int				dstartx;
	int				texx;
	int				texy;
}					t_sp;

typedef struct		s_ca
{
	double			cx;
	double			rdirx;
	double			rdiry;
	int				mapx;
	int				mapy;
	double			dx;
	double			dy;
	double			sdistx;
	double			sdisty;
	double			pwdist;
	int				stepx;
	int				stepy;
	int				lheight;
	int				dstart;
	int				dend;
	double			wallx;
	int				texx;
	int				texy;
	double			texpos;
}					t_ca;

typedef struct		s_cmap
{
	int				check;
	char			**c_map;
}					t_cmap;

typedef struct		s_game
{
	t_sp			cs;
	t_ca			ct;
	double			posx;
	double			posy;
	double			dirx;
	double			diry;
	double			px;
	double			py;
	long			width;
	long			height;
	void			*mlx;
	void			*win;
	t_img			img;
	unsigned int	**buf;
	double			*zbuf;
	int				**texture;
	double			mspeed;
	double			rspeed;

	int				flag;
	int				flag_pos;
	char			**worldmap;
	int				numsprites;

	t_sprite		*sprite;
	int				*sorder;
	double			*sdis;

	int				fcolor;
	int				ccolor;

	int				save;
	t_image			*image;
	t_cmap			map;
	int				hit;
	double			step;
	int				texn;
	int				stripe;
	int				d;
	int				color;
	int				key_flag;
}					t_game;

typedef struct		s_pair
{
	double			first;
	int				second;
}					t_pair;

int					main_loop(t_game *info);
void				cast_ray(t_game *info);
void				get_bit(t_game *info);
void				draw(t_game *info);
void				cast_sprite(t_game *info);
void				get_bit(t_game *info);
int					close_game(t_game *info);
void				check_win_size(t_game *info);
void				check_map(t_game *info);
void				set_color(t_game *info, int *x, int *texn, int *side);
void				put_error(char *str);
void				check_space_only(char ***line, int *i);
void				rotate_left(t_game *info);
void				rotate_right(t_game *info);
void				check_chara(t_game *info, int i, int j);
void				tex_free(t_game *info);
void				free_line(char ***line, int count);
void				free_buf(t_game *info);
void				free_rcf(char **str, int i);
void				init(t_game *info, char **argv, int argc);
int					deal_key(int key, t_game *info);

#endif
