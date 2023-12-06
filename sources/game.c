/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsl <rsl@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 19:35:25 by toteixei          #+#    #+#             */
/*   Updated: 2023/12/06 23:27:12 by rsl              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int     get_color(int *color)
{
    int r;
    int g;
    int b;

    r = color[0];
    g = color[1];
    b = color[2];
    return (r << 16 | g << 8 | b);
}

void	img_pixel_put(int x, int y, unsigned int color, t_cub3d *cub3d)
{
	int	mypixel;
	// int	alpha;//not used

	// alpha = 0; //not used
	if (x >= SCREEN_WIDTH || y >= SCREEN_HEIGHT || x < 0 || y < 0)
		return ;
	mypixel = (y * SCREEN_WIDTH) + x;
	if (cub3d->img.bpp != 32)
		color = mlx_get_color_value(cub3d->mlx, color);
    cub3d->img.addr[mypixel] = color;
	// if (cub3d->img.endian == 1)
	// {
	// 	cub3d->img.addr[mypixel] = alpha;
	// 	cub3d->img.addr[mypixel + 1] = (color >> 16) & 0xFF;
	// 	cub3d->img.addr[mypixel + 2] = (color >> 8) & 0xFF;
	// 	cub3d->img.addr[mypixel + 3] = (color) & 0xFF;
	// }
	// else
	// {
	// 	cub3d->img.addr[mypixel] = (color) & 0xFF;
	// 	cub3d->img.addr[mypixel + 1] = (color >> 8) & 0xFF;
	// 	cub3d->img.addr[mypixel + 2] = (color >> 16) & 0xFF;
	// 	cub3d->img.addr[mypixel + 3] = alpha;
	// }
}

void    ft_render_white_background(t_cub3d *cub3d)
{
    int x;
    int y;

    x = 0;
    while (x < SCREEN_WIDTH)
    {
        y = 0;
        while (y < SCREEN_HEIGHT / 2)
        {
            img_pixel_put(x, y, get_color(cub3d->config->c_color), cub3d);
            y++;
        }
        while (y < SCREEN_HEIGHT)
        {
            img_pixel_put(x, y, get_color(cub3d->config->fl_color), cub3d);
            y++;
        }
        x++;
    }
    mlx_put_image_to_window(cub3d->mlx, cub3d->win, cub3d->img.mlx, 0, 0);
}

void    ft_print_grid(t_cub3d *cub3d)
{
    int x;
    int y;

    x = 0;
    while (x < SCREEN_WIDTH)
    {
        y = 0;
        while (y < SCREEN_HEIGHT)
        {
            if (x % 20 == 0 || y % 20 == 0)
                img_pixel_put(x, y, 0x00000000, cub3d);
            y++;
        }
        x++;
    }
    mlx_put_image_to_window(cub3d->mlx, cub3d->win, cub3d->img.mlx, 0, 0);
}

void    print_a_square(int screen_x, int screen_y, int size, unsigned int color, t_cub3d *cub3d)
{
    int x;
    int y;

    x = screen_x;
    while (x < screen_x + size)
    {
        y = screen_y;
        while (y < screen_y + size)
        {
            img_pixel_put(x, y, color, cub3d);
            y++;
        }
        x++;
    }
}

void    print_a_sphere(int screen_x, int screen_y, int size, unsigned int color, t_cub3d *cub3d)
{
    int x;
    int y;
    int radius = size / 2;

    x = screen_x - radius;
    while (x < screen_x + size)
    {
        y = screen_y - radius;
        while (y < screen_y + size)
        {
            if (((x - screen_x) * (x - screen_x) + (y - screen_y) * (y - screen_y)) <= (radius * radius))
                img_pixel_put(x, y, color, cub3d);
            y++;
        }
        x++;
    }
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

// TOP CODE
// void    print_direction_line_of_player(t_cub3d *cub3d)
// {
//     t_point player;
//     t_point direction;

//     player.x = SCREEN_WIDTH - cub3d->config->n_column * 10 + (cub3d->cam.p_x * 10);
//     player.y = SCREEN_HEIGHT - cub3d->config->n_rows * 10 + (cub3d->cam.p_y * 10);
//     direction.x = player.x + (cub3d->cam.pd_x * 5);
//     direction.y = player.y + (cub3d->cam.pd_y * 5);
//     draw_line(cub3d, player, direction);
// }

void    print_direction_line_of_player(t_cub3d *cub3d)
{
    t_point player;
    t_point direction;
    t_point left_fov_line_end;
    t_point right_fov_line_end;

    player.x = SCREEN_WIDTH - cub3d->config->n_column * 10 + (cub3d->cam.p_x * 10);
    player.y = SCREEN_HEIGHT - cub3d->config->n_rows * 10 + (cub3d->cam.p_y * 10);

    direction.x = player.x + (cub3d->cam.pd_x * 5);
    direction.y = player.y + (cub3d->cam.pd_y * 5);

    //double fov_angle = cub3d->cam.fov * (M_PI / 180.0); // Convert FOV to radians
    double fixed_angle = M_PI / 6.0; // Adjust this value for the desired fixed angle

    double left_fov_angle = cub3d->cam.pa - fixed_angle;
    double right_fov_angle = cub3d->cam.pa + fixed_angle;

    // Calculate left FOV line end point
    left_fov_line_end.x = player.x + ((cub3d->cam.pd_x * cos(left_fov_angle)) * 5);
    left_fov_line_end.y = player.y + ((cub3d->cam.pd_y * sin(left_fov_angle)) * 5);

    // Calculate right FOV line end point
    right_fov_line_end.x = player.x + ((cub3d->cam.pd_x * cos(right_fov_angle)) * 5);
    right_fov_line_end.y = player.y + ((cub3d->cam.pd_y * sin(right_fov_angle)) * 5);

    draw_line(cub3d, player, direction);
    draw_line(cub3d, player, left_fov_line_end);
    draw_line(cub3d, player, right_fov_line_end);
}

//wrong end
// void print_fov_lines_of_player(t_cub3d *cub3d)
// {
//     t_point player;
//     t_point direction;
//     t_point left_fov_line_end;
//     t_point right_fov_line_end;

//     player.x = SCREEN_WIDTH - cub3d->config->n_column * 10 + (cub3d->cam.p_x * 10);
//     player.y = SCREEN_HEIGHT - cub3d->config->n_rows * 10 + (cub3d->cam.p_y * 10);

//     direction.x = player.x + (cub3d->cam.pd_x * 5);
//     direction.y = player.y + (cub3d->cam.pd_y * 5);

//     // Calculate the angle of the FOV lines relative to the player's direction
//     double fov_angle = cub3d->cam.fov * (M_PI / 180.0); // Convert FOV to radians
//     double fixed_angle = M_PI / 6.0; // Adjust this value as per your desired fixed angle

//     double left_fov_angle = cub3d->cam.pa - fixed_angle;
//     double right_fov_angle = cub3d->cam.pa + fixed_angle;

//     // Calculate left FOV line end point
//     left_fov_line_end.x = direction.x + ((cub3d->cam.pd_x * cos(left_fov_angle)) * 5);
//     left_fov_line_end.y = direction.y + ((cub3d->cam.pd_y * sin(left_fov_angle)) * 5);

//     // Calculate right FOV line end point
//     right_fov_line_end.x = direction.x + ((cub3d->cam.pd_x * cos(right_fov_angle)) * 5);
//     right_fov_line_end.y = direction.y + ((cub3d->cam.pd_y * sin(right_fov_angle)) * 5);

//     // Draw lines for the left and right FOV edges
//     draw_line(cub3d, direction, left_fov_line_end);
//     draw_line(cub3d, direction, right_fov_line_end);
// }


void    put_player_on_map(t_cub3d *cub3d)
{
    int screen_x = SCREEN_WIDTH - cub3d->config->n_column * 10 + (cub3d->cam.p_x * 10);
    int screen_y = SCREEN_HEIGHT - cub3d->config->n_rows * 10 + (cub3d->cam.p_y * 10);

    print_a_sphere(screen_x, screen_y, 5, 0x00FF0000, cub3d);
    print_direction_line_of_player(cub3d);
    // print_fov_lines_of_player(cub3d); //added
}

void    ft_print_map(t_cub3d *cub3d)
{
    int x;
    int y;
    int screen_x = SCREEN_WIDTH - cub3d->config->n_column * 10;
    int screen_y = SCREEN_HEIGHT - cub3d->config->n_rows * 10;

    x = 0;
    while (x < cub3d->config->n_rows)
    {
        y = 0;
        while (y < cub3d->config->n_column)
        {
            if (cub3d->config->map[x][y] == 1)
            {
                screen_x = SCREEN_WIDTH - cub3d->config->n_column * 10 + (y * 10);
                screen_y = SCREEN_HEIGHT - cub3d->config->n_rows * 10 + (x * 10);
                print_a_square(screen_x, screen_y, 10, 0x00000000, cub3d);
            }
            if (cub3d->config->map[x][y] == 0 || cub3d->config->map[x][y] == 3)
            {
                screen_x = SCREEN_WIDTH - cub3d->config->n_column * 10 + (y * 10);
                screen_y = SCREEN_HEIGHT - cub3d->config->n_rows * 10 + (x * 10);
                print_a_square(screen_x, screen_y, 10, 0x00FFFFFF, cub3d);
            }
            y++;
        }
        put_player_on_map(cub3d);
        x++;
    }
}

int    ft_render_game(t_cub3d *cub3d)
{
    //ft_render_white_background(cub3d);
    draw_rays_3d(cub3d);
    //ft_print_grid(cub3d);
    ft_print_map(cub3d);
    mlx_put_image_to_window(cub3d->mlx, cub3d->win, cub3d->img.mlx, 0, 0);
    return (0);
}