/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   constants.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stakabay <stakabay@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/09 12:13:51 by stakabay          #+#    #+#             */
/*   Updated: 2021/01/19 23:49:26 by stakabay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONSTANTS_H
# define CONSTANTS_H

# include <stdio.h>
# include <stdlib.h>
# include <math.h>
# include <string.h>
# include <float.h>
# include <unistd.h>
# include <errno.h>
# include <stdbool.h>
# include "libft/libft.h"
# include "GNL/get_next_line.h"
# include "bmp/bitmap.h"
# include "./minilibx_mms_20200219/mlx.h"

# define FALSE					0
# define TRUE					1
# define PI						3.14159265
# define TWO_PI					6.28318530
# define TILE_SIZE				64
# define ROWS					200
# define COLS					200
# define MINIMAP_SCALE_FACTOR	0.2

/*
** (60 * (PI / 180))
*/
# define FOV_ANGLE				1.04719755
# define NUM_TEXTURE			5

# define X_EVENT_KEY_PRESS		2
# define X_EVENT_KEY_EXIT		17
# define KEY_ESC				53
# define KEY_W					13
# define KEY_A					0
# define KEY_S					1
# define KEY_D					2
# define KEY_LEFT				123
# define KEY_RIGHT				124
# define KEY_UP					126
# define KEY_DOWN				125

typedef struct		s_readcub
{
	int				width;
	int				height;
	char			*nopath;
	char			*sopath;
	char			*wepath;
	char			*eapath;
	char			*txpath;
	char			*sppath;
	int				fr;
	int				fg;
	int				fb;
	unsigned int	floorcol;
	int				cr;
	int				cg;
	int				cb;
	unsigned int	ceilingcol;
	char			map[ROWS + 1][COLS + 1];
	char			bigmap[ROWS + 3][COLS + 3];
	double			player_x;
	double			player_y;
	int				sprite_num;
	int				rows;
	int				cols;
}					t_readcubtxt;

typedef struct		s_strplay
{
	float			x;
	float			y;
	float			width;
	float			height;
	int				turn_direction;
	int				walk_direction;
	int				lateralmove;
	float			rotation_angle;
	float			walk_speed;
	float			turn_speed;
	double			dir_x;
	double			dir_y;
	double			plane_x;
	double			plane_y;
	float			new_player_x;
	float			new_player_y;
	double			old_dir_x;
	double			old_plane_x;
	int				g_key_flag;
}					t_strplay;

typedef	struct		s_texture
{
	void			*img;
	int				*data;
	int				size_l;
	int				bpp;
	int				endian;
	int				width;
	int				height;
}					t_texture;

typedef	struct		s_sprite
{
	float			x;
	float			y;
	float			sprite_distance;
	struct s_sprite	*next;
}					t_sprite;

typedef	struct		s_img
{
	void			*img;
	int				*data;
	int				size_l;
	int				bpp;
	int				endian;
}					t_img;

typedef	struct		s_sprite_ray
{
	float			ray_angle;
	float			wall_hit_x;
	float			wall_hit_y;
	float			distance;
	int				was_hit_vertical;
	int				is_ray_facing_up;
	int				is_ray_facing_down;
	int				is_ray_facing_left;
	int				is_ray_facing_right;
	int				wall_hit_content;
	int				found_sprite;
}					t_sprite_ray;

typedef	struct		s_projection
{
	float			perp_dis;
	float			dis_proj_plane;
	float			proj_height;
	int				strip_height;
	int				top_pixel;
	int				bottom_pixel;
	int				tex_offset_x;
	int				tex_offset_y;
	int				texel_color;
	int				distance_from_top;
	int				tex_x;
}					t_projection;

typedef	struct		s_ray
{
	float			ray_angle;
	float			wall_hit_x;
	float			wall_hit_y;
	float			distance;
	int				was_hit_vertical;
	int				is_ray_facing_up;
	int				is_ray_facing_down;
	int				is_ray_facing_left;
	int				is_ray_facing_right;
	int				wall_hit_content;
	float			ray_dir_x;
	float			ray_dir_y;
}					t_ray;

typedef	struct		s_ray_prop
{
	int				is_ray_facing_down;
	int				is_ray_facing_up;
	int				is_ray_facing_right;
	int				is_ray_facing_left;
	float			xintercept;
	float			yintercept;
	float			xstep;
	float			ystep;
	float			next_horz_touch_x;
	float			next_horz_touch_y;
}					t_ray_prop;

typedef	struct		s_horzvert
{
	int				found_horz_wall_hit;
	float			horz_wall_hit_x;
	float			horz_wall_hit_y;
	int				horz_wall_content;
	int				found_vert_wall_hit;
	float			vert_wall_hit_x;
	float			vert_wall_hit_y;
	int				vert_wall_content;
}					t_horzvert;

typedef struct		s_sprite_dis
{
	double			sprite_x;
	double			sprite_y;
	double			inv_det;
	double			transform_x;
	double			transform_y;
	int				sprite_screen_x;
	int				v_move_screen;
	int				sprite_height;
	int				draw_start_y;
	int				draw_end_y;
	int				sprite_width;
	int				draw_start_x;
	int				draw_end_x;
	int				stripe;
	int				tex_x;
	int				y;
	int				d;
	int				tex_y;
	int				color;
}					t_sprite_dis;

typedef	struct		s_game
{
	void			*mlx;
	void			*win;
	t_img			img;
	t_texture		*texture;
	t_strplay		player;
	t_ray			*rays;
	t_sprite		*sprite;
	t_sprite_ray	*sprite_ray;
	t_sprite_dis	sp_disc;
	int				sprite_num;
	t_readcubtxt	cub;
	t_projection	proj;
	t_ray_prop		ray_prop;
	t_horzvert		horzvert;
	int				num_rays;
	double			*z_buffer;
	int				bmp;
}					t_game;

int					readcubtxt(t_game *game, char **argv, int argc);
void				project_sprite(t_game *game);
void				write_bmp_simple_file(const char *filename, t_game *game);
int					ft_error(int error_num, int return_num, char *error_str);
void				sort_sprite(t_game *game);
int					init(t_game *game, char **argv, int argc);
int					map_has_wall_at(t_game *game, float x, float y);
int					deal_key(int key, t_game *game);
void				cast_all_rays(t_game *game);
void				vert_ray_grid_intersetion(float ray_angle, t_game *game);
void				hor_ray_grid_intersetion(float ray_angle, t_game *game);
void				set_ray_dic(float horz_hit, \
								float vert_hit, int id, t_game *game);
void				render_player(t_game *game);
void				render_rays(t_game *game);
void				render_map(t_game *game);
void				generate_3d_projection(t_game *game);

#endif
