/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_rays.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdurand <jdurand@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/17 14:08:39 by jdurand           #+#    #+#             */
/*   Updated: 2019/11/21 17:46:26 by jdurand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube3D.h"

void 	ft_setup_rays(t_data *data, int **map)
{
	int 	i;
	double pas = 60 / (double)data->R[0];
	double len = 0.001;

	i = 0;
	if (!(data->vectors = (t_vector*)malloc(data->R[0] * sizeof(t_vector))))
		return ;
	if (!(data->dda = (t_dda*)malloc(data->R[0] * sizeof(t_dda))))
		return ;
	data->angle = ft_get_angle(data, map);
	while (i < data->R[0])
	{
		data->vectors[i].angle_rela = (double)i * pas;
	//	printf("1: %lf ", data->vectors[i].angle_rela);
		i++;
	}
}
void 	do_rays(t_data *data)
{
	int i = 0;
	double len = 0.1;

	while (i < data->R[0])
	{
	//	len = 0.1;
		ft_setray(data, i);
		while (data->map[(int)data->vectors[i].y1][(int)data->vectors[i].x1] != 1)
		{
		//	printf("%lf, %lf\n", data->vectors[i].rotx, data->vectors[i].roty);
			ft_dda(data, i);
		//	printf("%lf %lf\n", data->dda[i].movex, data->dda[i].movey);
		//	printf("la");
			if (data->dda[i].movex < data->dda[i].movey && data->dda[i].movex > 0.000001)
				len = data->dda[i].movex;
			else if (data->dda[i].movey)
				len = data->dda[i].movey;
			printf("len: %.15lf\n", len);
			data->vectors[i].x1 += (len * data->vectors[i].rotx);
			data->vectors[i].y1 -= (len * data->vectors[i].roty);
		}
		i++;
	}
	ft_do_colum(data); // a regler
	mlx_put_image_to_window(data->mlx_p, data->mlx_wd, data->mlx_img, 0, 0);
}

void 	ft_setray(t_data *data, int i)
{
	double pas;

	pas = 60 / (double)data->R[0];
	data->vectors[i].x1 = data->posx;
	data->vectors[i].y1 = data->posy;
	data->vectors[i].angle = data->angle - (60 / 2) + ((double)i * pas);
	if (data->vectors[i].angle >= 360)
		data->vectors[i].angle = 0;
	else if (data->vectors[i].angle < 0)
		data->vectors[i].angle = 360;
	data->vectors[i].rotx = cos(ft_toradian(data->vectors[i].angle));
	data->vectors[i].roty = sin(ft_toradian(data->vectors[i].angle));

//	if (i == data->R[0] / 2) //|| i == 0 || i == data->R[0] - 1)
	//	printf(GREEN "ray %d: x1: %lf, y1: %lf\nangle : %lf\n, rotx : %lf, roty: %lf\n"
//		RESET, i, data->vectors[i].x1, data->vectors[i].y1, data->vectors[i].angle,
//		data->vectors[i].rotx, data->vectors[i].roty);
}

void 	ft_do_colum(t_data *data)
{
	unsigned long int		j = 0;
	int		hp;
//	int 	diff;
	int		i = 0;
	double 	distance;

	while (i < data->R[0])
	{
	if (i < data->R[0])
		distance = get_dist(data, i) * cos(ft_toradian(30 - data->vectors[i].angle_rela));
	else if (i > data->R[0])
		distance = get_dist(data, i) * cos(ft_toradian(data->vectors[i].angle_rela - 30));
		if (distance < 1)
			distance = 1;
		hp = data->R[1] / distance;
	//		printf("%d, %lf\n", i, data->vectors[i].angle_rela);
		j = (data->R[1] / 2 * data->size_line) - (hp / 2 * data->size_line);
			while (j >= (data->R[1] / 2 * data->size_line) - (hp / 2 * data->size_line) && j <= (data->R[1] / 2 * data->size_line) + (hp / 2 * data->size_line))
			{
				data->img[j + (data->R[0] - i) * 4 + 0] = (char)85;
				data->img[j + (data->R[0] - i) * 4 + 1] = (char)85;
				data->img[j + (data->R[0] - i) * 4 + 2] = (char)85;
				data->img[j + (data->R[0] - i) * 4 + 3] = (char)0;
				j += data->size_line;
			}
		i++;
	}
//	printf("calcul angle R0: %lf - %lf = %lf\nRmax %lf - %lf = %lf\nRmin %lf - %lf = %lf\n"
//			, data->vectors[data->R[0] / 2].angle, data->angle, data->vectors[data->R[0] / 2].angle - data->angle,
//			data->vectors[data->R[0] - 50].angle, data->angle, data->vectors[data->R[0] - 50].angle - data->angle,
//			data->vectors[50].angle, data->angle, data->vectors[50].angle - data->angle);
}

double 	get_dist(t_data *data, int i)
{
	double distance;

	distance = sqrt(pow(data->vectors[i].x1 - data->posx, 2) + pow(data->vectors[i].y1 - data->posy, 2));
	return (distance);
}
