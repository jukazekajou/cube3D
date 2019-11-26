/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube3D.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdurand <jdurand@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/07 13:55:14 by jdurand           #+#    #+#             */
/*   Updated: 2019/11/26 14:51:56 by jdurand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUBE3D_H
# define CUBE3D_H

# include "../libft/libft.h"
# include <math.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <stdio.h>
# include <mlx.h>

# define pi 3.14159265
# define speed 300
# define speed_angle 2;
# define ABS(n) (n > 0) ? (n) : (-n)


# define GREEN   "\x1b[32m"
# define RESET   "\x1b[0m"

typedef struct	s_vector
{
	float	x1;
	float	y1;
	float	rotx;
	float	roty;
	float	angle;
	float 	angle_rela;
	int		wall_type;
	float	dist_towall;
}				t_vector;

typedef	struct	s_intercept
{
	float	delta;
	float	x;
	float	y;
	float	dist;
}				t_intercept;

typedef struct	s_dda
{
	float	dx;
	float	dy;
	int		xsign;
	int		ysign;
}				t_dda;

typedef struct	s_data
{
	int					check;
	int 				width;
	int					height;
	float				posx;
	float				posy;
	float				angle;
	int					R[2];
	char				*NO;
	char				*SO;
	char 				*WE;
	char 				*ES;
	char 				*S;
	unsigned int		F;
	unsigned int		C;
	char				*img;
	void 				*mlx_p;
	void 				*mlx_wd;
	void 				*mlx_img;
	int 				size_line;
	int 				endian;
	int 				bit_p_p;
	int 				**map;
	struct s_vector 	*vec;
	struct s_dda		*dda;
}				t_data;

int		ft_iserror(int code);
int		**ft_parse_stuff(t_data *data, int fd);
void 	parse_map(t_data *data, char *line);
void 	parse_color(t_data *data, char *line);
void 	parse_path(t_data *data, char *line);
char	*pathing(char *path, char *line, int *check);
void 	parse_res(t_data *data, char *line);
void 	coloring(unsigned int *rgb, char *line, int *check);

int 	ft_game_loop(t_data *data, int **map);

int 			ft_setup_mlx(t_data *data, int **map);
void 	ft_setup_rays(t_data *data, int **map);
int 	ft_main_loop(int keycode, void *params);

unsigned int 	ft_rgb(int r, int g, int b);
float 			ft_toradian(float angle);
int 	ft_isargvalid(char c);
int		ft_search_arg(char *line, char *set);

int 	ft_get_angle(t_data *data, int **map);

void 	do_rays(t_data *data);
void 	ft_setray(t_data *data, int i);
float 	get_dist(t_data *data, int i);
void 	ft_do_colum(t_data *data);

void 	ft_dda(t_data *data, int i);
void 	ft_perform_dda(t_data *data, int i);
float	get_theta(t_data *data, int i);
void 	do_dist(t_data *data, t_intercept *x_, t_intercept *y_, int i);

int 	ft_dox(t_data *data, t_intercept *x_, int i);
int 	ft_doy(t_data *data, t_intercept *y_, int i);

void 	ft_init_deltas(t_data *data, t_intercept *x_, t_intercept *y_, int i);

unsigned int 	ft_choose_color(t_data *data, int i);

void 	ft_keyboard_loop(t_data *data, int keycode);

#endif
