/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toteixei <toteixei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 19:35:25 by toteixei          #+#    #+#             */
/*   Updated: 2023/12/08 16:25:51 by toteixei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	get_color(int *color)
{
	int	r;
	int	g;
	int	b;

	r = color[0];
	g = color[1];
	b = color[2];
	return (r << 16 | g << 8 | b);
}

void	img_pixel_put(int x, int y, unsigned int color, t_cub3d *cub3d)
{
	int	mypixel;

	if (x >= SCREEN_WIDTH || y >= SCREEN_HEIGHT || x < 0 || y < 0)
		return ;
	mypixel = (y * SCREEN_WIDTH) + x;
	if (cub3d->img.bpp != 32)
		color = mlx_get_color_value(cub3d->mlx, color);
	cub3d->img.addr[mypixel] = color;
}

void	draw_line_bis(t_cub3d *cub3d, t_point p1, t_point p2, t_line line)
{
	while (p1.x != p2.x || p1.y != p2.y)
	{
		if (p1.x != 0)
			img_pixel_put(p1.x, p1.y, p1.color, cub3d);
		line.e2 = 2 * line.error;
		if (line.e2 > -line.dy)
		{
			line.error -= line.dy;
			p1.x += line.sx;
		}
		if (line.e2 < line.dx)
		{
			line.error += line.dx;
			p1.y += line.sy;
		}
	}
}

void	draw_line(t_cub3d *cub3d, t_point p1, t_point p2)
{
	t_line	line;

	line.temp = p1;
	line.dx = abs(p2.x - p1.x);
	line.dy = abs(p2.y - p1.y);
	if (p2.x > p1.x)
		line.sx = 1;
	else
		line.sx = -1;
	if (p2.y > p1.y)
		line.sy = 1;
	else
		line.sy = -1;
	line.error = line.dx - line.dy;
	draw_line_bis(cub3d, p1, p2, line);
}

int	ft_render_game(t_cub3d *cub3d)
{
	draw_rays_3d(cub3d);
	ft_print_map(cub3d);
	mlx_put_image_to_window(cub3d->mlx, cub3d->win, cub3d->img.mlx, 0, 0);
	return (0);
}
