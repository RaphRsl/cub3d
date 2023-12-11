/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   deal_key.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toteixei <toteixei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 09:40:03 by toteixei          #+#    #+#             */
/*   Updated: 2023/12/11 16:10:49 by toteixei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	deal_key(int key, t_cub3d *cub3d)
{
	if (key == ESC)
		end_program(cub3d);
	else if (key == W_KEY || key == KB_UP)
		move_forward(cub3d);
	else if (key == S_KEY || key == KB_DOWN)
		move_backward(cub3d);
	else if (key == KB_RIGHT)
		rotate_left(&cub3d->cam, cub3d->cam.rot_speed);
	else if (key == KB_LEFT)
		rotate_right(&cub3d->cam, cub3d->cam.rot_speed);
	else if (key == A_KEY)
		move_to_the_left(cub3d);
	else if (key == D_KEY)
		move_to_the_right(cub3d);
	return (0);
}

int	deal_mouse(int x, int y, t_cub3d *cub3d)
{
	(void)y;
	if (cub3d->cam.x_mouse == 0)
		cub3d->cam.x_mouse = x;
	else
	{
		if (x > cub3d->cam.x_mouse)
		{
			rotate_right(&cub3d->cam, cub3d->cam.rot_mouse);
			cub3d->cam.x_mouse = x;
		}
		else if (x < cub3d->cam.x_mouse)
		{
			rotate_left(&cub3d->cam, cub3d->cam.rot_mouse);
			cub3d->cam.x_mouse = x;
		}
	}
	return (0);
}
