/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_graph.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdurand <jdurand@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/12 17:26:07 by jdurand           #+#    #+#             */
/*   Updated: 2019/11/17 15:12:07 by jdurand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube3D.h"

#define H 1024
#define W 956

unsigned int 	ft_rgb(int r, int g, int b)
{
	color = 0;
	color |= (b << 0);
	color |= (g << 8);
	color |= (r << 16);
	return (color);
}

double ft_get_d(t_data *data, int **map)
{
	double rayx, rayy;
	double dirx, diry;

	rayx = data->posx; rayy = data->posy;
	dirx = data->posx; diry = 0;
	printf("in d90\n");
	printf("dir: %d\n", map[(int)rayy][(int)rayx]);
	while (map[(int)rayy][(int)rayx] != 1)
	{
		if (rayx != dirx)
			rayx += 0.01;
		if (rayy >= diry)
			rayy -= 0.01;

	//	printf("rayx: %lf || rayy: %lf\n", rayx, rayy);
	}
	return (sqrt(pow(rayx - data->posx, 2.0) + pow(rayy - data->posy, 2.0)));
}

void 	ft_do_graphism(int **map, t_data *data)
{
	int i = 0; int j = 0;
	unsigned int color = 0;

	data->map = map;
	if ((data->mlx_p = mlx_init()))
		printf("succes mlx\n");
	data->mlx_wd = mlx_new_window(data->mlx_p, data->R[0], data->R[1], "onanisme");
	if (data->mlx_wd)
		printf("%p\n", data->mlx_wd);
	data->mlx_img = mlx_new_image(data->mlx_p, data->R[0], data->R[1]);
	if (!data->mlx_img)
		return ;
	data->img = mlx_get_data_addr(data->mlx_img, &(data->bit_p_p), &(data->size_line), &(data->endian));
	printf("bpp: %d, sizeline: %d, endian: %d\n", data->bit_p_p, data->size_line, data->endian);
	ft_setup(data, map);
	//first ray and creation of vector_tab

	mlx_key_hook(data->mlx_wd, ft_keyboard, data);
	mlx_loop(data->mlx_p);

//	}
}

/*
H * size_line = nombre de bits dans img

*/
/*
void 	ft_do_graphism(int **map, t_data *data)
{
	void 	*mlx_p;
	void 	*mlx_wd;
	int i = 0; int j = 0;
	unsigned int color = 0;

	if ((mlx_p = mlx_init()))
		printf("succes mlx\n");
	mlx_wd = mlx_new_window(mlx_p, W, H, "onanisme");
	if (mlx_wd)
		printf("%p\n", mlx_wd);

	while (j < H)
		{
			while (i < W)
				mlx_pixel_put(mlx_p, mlx_wd, i++, j, ft_rgb(&color, 0, 0, 0));
			i = 0;
			j++;
		}
	i = 0; j = 0;

	printf("x: %lf, y: %lf\n", data->posx, data->posy);

	int taille_mur; double d_eucli;

	while (map[(int)data->posy][(int)data->posx] != 1)
	{
		printf("%.25lf\n", d_eucli = ft_get_d_90(data, map));
		taille_mur = H / d_eucli;
		while (j < H)
		{
	 	if (j > H / 2 - (taille_mur / 2) && j < H / 2 + (taille_mur / 2))
	 		while (i < W)
	 			mlx_pixel_put(mlx_p, mlx_wd, i++, j, ft_rgb(&color, 255, 255, 0));
			j++;
			i = 0;
		}
		j = 0;
		data->posy -= 0.21;
	}
	mlx_loop(mlx_p);
}*/





/*	while (j < H)
	{
		while (i < W)
			mlx_pixel_put(mlx_p, mlx_wd, i++, j, color);
		i = 0;
		j++;
	}
	ft_rgb_code(&color, 147, 112, 219);
	j = H / 4; i = W / 4;
	while (j < (H - H / 4))
	{
		while (i < W - W / 4)
			mlx_pixel_put(mlx_p, mlx_wd, i++, j, color);
		i = W / 4; j++;
	}*/
