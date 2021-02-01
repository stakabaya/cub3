//gcc -g -fsanitize=undefined,address map_2d.c ./minilibx-linux/libmlx.a -lXext -lX11 -lm
//-lmが必要
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
//#include "minilibx-linux/mlx.h"
#include "mlx.h"

#define X_EVENT_KEY_PRESS		2
#define X_EVENT_KEY_EXIT		17 //Exit program key code

# define KEY_ESC			65307
# define KEY_W			119
# define KEY_A			97
# define KEY_S			115
# define KEY_D			100

# define TILE_SIZE 32
# define ROWS 11
# define COLS 15
# define WIDTH COLS * TILE_SIZE
# define HEIGHT ROWS * TILE_SIZE

# define TO_COORD(X, Y) ((int)floor(Y) * WIDTH + (int)floor(X))
//整数に切り替える　小数点以下は切り捨て

# define PI 3.1415926535

// int g_player_x = 50;
// int g_player_y = 50;
int g_key_flag = 1;

typedef struct	s_player
{
	double	posX; //x and y start position
	double	posY; //x and y start position
	double	dirX; //initial direction vector 初期方向ベクトル
	double	dirY; //initial direction vector 初期方向ベクトル
	double	pa; //player アングル？？
	double	planeX; //the 2d raycaster version of camera plane 2Dレイキャスター版カメラプレーン
	double	planeY; //the 2d raycaster version of camera plane 2Dレイキャスター版カメラプレーン

	double	time; //time of current frame
	double	oldTime; //time of previous frame
}				t_player;

typedef struct	s_img
{
	void	*img;
	int		*data;

	int		size_l;
	int		bpp;
	int		endian;
}				t_img;

typedef struct	s_game
{
	void	*mlx;
	void	*win;
	t_img	img;
	t_player player;

	int		map[ROWS][COLS];
}				t_game;

void			my_rec_put(t_game *game, double x, double y, int color)
{
	//int or double?
	double x_end = x + 10;
	double y_end = y + 10;
	double y_tmp = y;

	while (x <= x_end)
	{
		y = y_tmp;
		while (y <= y_end)
		{
			mlx_pixel_put(game->mlx, game->win, x, y, color);
			y++;
		}
		x++;
	}
}

int		deal_key(int key_code, t_game *game)
{
	if (key_code == KEY_ESC)
		exit(0);
	else if (key_code == KEY_W)
		game->player.posY -= 0.1;
		if (game->player.pa < 0) 
		{
			game->player.pa += 2 * PI;
			game->player.dirX = cos(game->player.pa) * 5;
			game->player.dirY = sin(game->player.pa) * 5;
		} 
	else if (key_code == KEY_S)
		game->player.posY += 5;
	else if (key_code == KEY_A)
		game->player.posX -= 5;
	else if (key_code == KEY_D)
		game->player.posX += 5;
	g_key_flag = 1;
	return (0);
}

//Draw the line by DDA algorithm
void	draw_line(t_game *game, double x1, double y1, double x2, double y2)
{
	double	deltaX;
	double	deltaY;
	double	step;

	deltaX = x2 - x1;
	deltaY = y2 - y1;
	step = (fabs(deltaX) > fabs(deltaY)) ? fabs(deltaX) : fabs(deltaY);
	deltaX /= step;
	deltaY /= step;
	while (fabs(x2 - x1) > 0.01 || fabs(y2 - y1) > 0.01)
	{
		game->img.data[TO_COORD(x1, y1)] = 0xb3b3b3;
		x1 += deltaX;
		y1 += deltaY;
	}
}

void 	draw_lines(t_game *game)
{
	int		i;
	int		j;

	i = 0;
	while (i < COLS)
	{
		draw_line(game, i * TILE_SIZE, 0, i * TILE_SIZE, HEIGHT);
		i++;
	}
	draw_line(game, COLS * TILE_SIZE - 1, 0, COLS * TILE_SIZE - 1, HEIGHT);
	j = 0;
	while (j < ROWS)
	{
		draw_line(game, 0, j * TILE_SIZE, WIDTH, j * TILE_SIZE);
		j++;
	}
	draw_line(game, 0, ROWS * TILE_SIZE - 1, WIDTH, ROWS * TILE_SIZE - 1);
}

void	draw_rectangle(t_game *game, int x, int y)
{
	int i;
	int j;

	x *= TILE_SIZE;
	y *= TILE_SIZE;
	i = 0;
	while (i < TILE_SIZE)
	{
		j = 0;
		while (j < TILE_SIZE)
		{
			game->img.data[(y  + i) * WIDTH + x + j] = 0xFFFFFF;
			j++;
		}
		i++;
	}
}

void	draw_rectangles(t_game *game)
{
	int		i;
	int		j;

	i = 0;
	while (i < ROWS)
	{
		j = 0;
		while (j < COLS)
		{
			if (game->map[i][j] == 1)
				draw_rectangle(game, j, i);
			j++;
		}
		i++;
	}
}

// int 	close(t_game *game)
// {
// 		exit(0);
// }

void	game_init(t_game *game)
{	
	int map[ROWS][COLS] = {
	{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1},
	{1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 1},
	{1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 1, 1, 1, 1, 1, 0, 0, 0, 1, 1, 1, 1, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}
	};
	memcpy(game->map, map, sizeof(int) * ROWS * COLS);
}

void	window_init(t_game *game)
{
	game->mlx = mlx_init();
	game->win = mlx_new_window(game->mlx, WIDTH, HEIGHT, "cub3D");
}

void	img_init(t_game *game)
{
	game->img.img = mlx_new_image(game->mlx, WIDTH, HEIGHT);
	game->img.data = (int *)mlx_get_data_addr(game->img.img, &game->img.bpp, &game->img.size_l, &game->img.endian);
}

int		main_loop(t_game *game)
{
	if (g_key_flag == 1)
	{
		draw_rectangles(game);
		draw_lines(game);
		mlx_put_image_to_window(game->mlx, game->win, game->img.img, 0, 0);
		my_rec_put(game, game->player.posX, game->player.posY, 0x00FF0000);
	}
	g_key_flag = 0;
	return (0);
}

int		main(void)
{
	t_game game;

	game.player.posX = 22, game.player.posY = 12;  //x and y start position
	game.player.dirX = -1, game.player.dirY = 0; //initial direction vector 初期方向ベクトル
	game.player.planeX = 0, game.player.planeY = 0.66; //the 2d raycaster version of camera plane 2Dレイキャスター版カメラプレーン

	game.player.time = 0; //time of current frame
	game.player.oldTime = 0; //time of previous frame

	game_init(&game);
	window_init(&game);
	img_init(&game);
	mlx_hook(game.win, X_EVENT_KEY_PRESS, 1, &deal_key, &game); //key入力によるplayerの移動
	mlx_loop_hook(game.mlx, &main_loop, &game); //map,player 描画部分
	mlx_loop(game.mlx);
}


