#include "mlx.h"
#include "constants.h"
#include<unistd.h>
#include<stdlib.h>
#include<math.h> 
#include <string.h>
#include <stdlib.h>

# define X_EVENT_KEY_PRESS		2



///
static	char	*setnum(char *num, int keta, int n)
{
	int flag;

	flag = 1;
	if (n < 0)
	{
		num[0] = '-';
		n *= -1;
		flag = 0;
	}
	num[keta--] = '\0';
	while (keta > 0)
	{
		num[keta--] = (n % 10) + '0';
		n /= 10;
	}
	if (flag == 1)
		num[0] = (n % 10) + '0';
	return (num);
}

void			ft_putnbr_fd(int n, int fd)
{
	int		keta;
	int		tmp;
	char	num[100];

	if (n == -2147483648)
	{
		setnum(num, 10, -214748364);
		num[10] = '8';
		write(fd, num, strlen(num));
		return ;
	}
	keta = 1;
	if (n < 0)
		keta++;
	tmp = n;
	while (tmp /= 10)
		keta++;
	setnum(num, keta, n);
	write(fd, num, strlen(num));
}
////

const int map[MAP_NUM_ROWS][MAP_NUM_COLS] = {
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 ,1, 1, 1, 1, 1, 1, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}
};

typedef struct	s_strplay
{
    float	x; //座標x
    float	y; //座標y
    float	width; //Playerのx方向の大きさ
    float	height; //Playerのy方向の大きさ
    int		turnDirection; // Playerの,回転する向き -1 for left, +1 for right
    int		walkDirection; // Playerの進退　-1 for back, +1 for front
    float	rotationAngle; // Playerの向いている角度
    float	walkSpeed; //進むスピード
    float	turnSpeed; //turnする大きさ
}				t_strplay;

typedef struct	s_img
{
	void	*img;
	int		*data;

	int		size_l;
	int		bpp;
	int		endian;
}				t_img;

typedef struct	s_flag
{
    void		*mlx;
    void		*win;

	t_strplay	player;
	t_img		img;
	int			i;
}				t_flag;

void setup(t_flag *ptr) {
    ptr->player.x = WINDOW_WIDTH / 2;
    ptr->player.y = WINDOW_HEIGHT / 2;
    ptr->player.width = 1;
    ptr->player.height = 1;
    ptr->player.turnDirection = 0;
    ptr->player.walkDirection = 0;
    ptr->player.rotationAngle = PI / 2; //90°　180°=PI=3.14
    ptr->player.walkSpeed = 100;
    ptr->player.turnSpeed = 10 * (PI / 180); //45°をラジアンに
}

int     deel_key(int key, t_flag *ptr)
{
    //t_flag  *ptr;
	//ptr = (t_flag *)param;
	ft_putnbr_fd(ptr->i, 1);
	//mlx_clear_window(ptr->mlx,ptr->win);

	if (key == ESCAPE) //Quit the program when ESC key pressed
		exit(0);
	//if (key == ESCAPE)
	//	mlx_destroy_window (ptr->mlx, ptr->win);
	else if (key == Up_Arrow)
	{
		write(1, "x",1);
		ptr->i += 10;
		ptr->player.x += cos(ptr->player.rotationAngle);
		ptr->player.y += sin(ptr->player.rotationAngle);
		//ptr->player.walkDirection = +1;
	}
	else if (key == Down_Arrow)
	{
		ptr->player.x -= cos(ptr->player.rotationAngle);
		ptr->player.y -= sin(ptr->player.rotationAngle);
	}
		//ptr->player.walkDirection = -1;
	else if (key == Right_Arrow)
		ptr->player.rotationAngle += 1 * ptr->player.turnSpeed;
		//ptr->player.turnDirection = +1;
	else if (key == Left_Arrow)
		ptr->player.rotationAngle -=1 * ptr->player.turnSpeed;
		//ptr->player.turnDirection = -1;
	
return (0);
}

void renderMap(void *param) {
	int i;
	int j;
	int k;
	int m;
	int tileX;
	int tileY;
	int tileColor;
	t_flag  *ptr;

	i = 0;
	ptr = (t_flag *)param;
	while(i < MAP_NUM_ROWS)
    {
		j = 0;
		while(j < MAP_NUM_COLS)
		{
			tileColor = map[i][j] != 0 ? 0xFFFFFF : 0;
			tileX = j * TILE_SIZE;
			tileY = i * TILE_SIZE;
				k = 0;
				while(k < TILE_SIZE)
				{
					m = 0;
					while(m < TILE_SIZE)
					{
						mlx_pixel_put(ptr->mlx, ptr->win, (tileX + m), (tileY + k), tileColor);
						m++;
					}
					k++;
				}
			j++;
		}
		i++;
    }
}

void renderPlayer(t_flag *ptr)
{
	float 	i;
	float 	j;
	float	cosAng;
	float	sinAng;
	int		cosSing;
	int		sinSing;

	cosAng = cos(ptr->player.rotationAngle);
	sinAng = sin(ptr->player.rotationAngle);
	cosSing = cosAng >= 0 ? 1 : -1;
	sinSing = sinAng >= 0 ? 1 : -1;
	if(cosAng < 0)
		cosAng *= -1;
	if(sinAng < 0)
		sinAng *= -1;

	i = 0;
	//j = 0;

	while(i <= 40)
	//while((i <= cosAng) || (j <= sinAng))
	{
		mlx_pixel_put(ptr->mlx, ptr->win, ptr->player.x + ((cosAng * i) * cosSing), ptr->player.y + ((sinAng * i) * sinSing) , 0xFFFFFF);
		//if(i <= cosAng)
			i++;
		//if(j <= sinAng)
			//j++;
	}
}

void movePlayer(t_flag *ptr)
{
	float moveStep;
	float newPlayerX;
	float newPlayerY;

    //ptr->player.rotationAngle += ptr->player.turnDirection * ptr->player.turnSpeed;// * deltaTime;
    //moveStep = ptr->player.walkDirection * ptr->player.walkSpeed;// * deltaTime;

    //newPlayerX = ptr->player.x + cos(ptr->player.rotationAngle) * moveStep;
    //newPlayerY = ptr->player.y + sin(ptr->player.rotationAngle) * moveStep;

    //if (!mapHasWallAt(newPlayerX, newPlayerY)) {
        //ptr->player.x = newPlayerX;
        //ptr->player.y = newPlayerY;
    //}

}

int render(void *param)
{
	t_flag	*ptr;
	ptr = (t_flag *)param;

	//renderMap(ptr);
	renderPlayer(ptr);
	movePlayer(ptr);
	return(0);
}


int main( )
{
    void    		*mlx_ptr;
    void   			*win_ptr;
    t_flag  		*ptr;

	ptr->i = 0;
	
    ptr = (t_flag *)malloc(sizeof(t_flag));
    
	setup(ptr);
	mlx_ptr = mlx_init();
	win_ptr = mlx_new_window(mlx_ptr, WINDOW_WIDTH, WINDOW_HEIGHT, "mlx 42");//SDL_createWindow
	ptr->mlx = mlx_ptr;
	ptr->win = win_ptr;
	ft_putnbr_fd(ptr->i, 1);

	ptr->img.img = mlx_new_image(ptr->mlx, WINDOW_WIDTH, WINDOW_HEIGHT);
	ptr->img.data = (int *)mlx_get_data_addr(ptr->img.img, &ptr->img.bpp, &ptr->img.size_l, &ptr->img.endian);
	mlx_hook(win_ptr, X_EVENT_KEY_PRESS, 1, &deel_key, &ptr);
	//mlx_hook(win_ptr, X_EVENT_KEY_PRESS, 1, &deel_key, &ptr); //int	mlx_hook(void *win_ptr, int x_event, int x_mask, int (*funct)(), void *param);
	//mlx_key_hook(win_ptr, deel_key, ptr);
		
	mlx_loop_hook(mlx_ptr,render, ptr);
	mlx_loop(mlx_ptr);
	//mlx_pixel_put(ptr->mlx, ptr->win, WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2, 0xFFFFFF);
}


