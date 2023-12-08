/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera_movement.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toteixei <toteixei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 15:03:44 by toteixei          #+#    #+#             */
/*   Updated: 2023/12/08 16:35:01 by toteixei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	move_to_the_right(t_cub3d *cub3d)
{
	if (!is_wall(cub3d->cam.p_x - (cub3d->cam.pd_y * (cub3d->cam.move_speed
					+ 0.01)), cub3d->cam.p_y + (cub3d->cam.pd_x
				* (cub3d->cam.move_speed + 0.01)), cub3d))
	{
		cub3d->cam.p_x -= (cub3d->cam.pd_y * cub3d->cam.move_speed);
		cub3d->cam.p_y += (cub3d->cam.pd_x * cub3d->cam.move_speed);
	}
}

void	move_to_the_left(t_cub3d *cub3d)
{
	if (!is_wall(cub3d->cam.p_x + (cub3d->cam.pd_y * (cub3d->cam.move_speed
					+ 0.01)), cub3d->cam.p_y - (cub3d->cam.pd_x
				* (cub3d->cam.move_speed + 0.01)), cub3d))
	{
		cub3d->cam.p_x += (cub3d->cam.pd_y * cub3d->cam.move_speed);
		cub3d->cam.p_y -= (cub3d->cam.pd_x * cub3d->cam.move_speed);
	}
}

void	move_forward(t_cub3d *cub3d)
{
	if (!is_wall(cub3d->cam.p_x + (cub3d->cam.pd_x * (cub3d->cam.move_speed
					+ 0.01)), cub3d->cam.p_y + (cub3d->cam.pd_y
				* (cub3d->cam.move_speed + 0.01)), cub3d))
	{
		cub3d->cam.p_x += (cub3d->cam.pd_x * cub3d->cam.move_speed);
		cub3d->cam.p_y += (cub3d->cam.pd_y * cub3d->cam.move_speed);
	}
}

void	move_backward(t_cub3d *cub3d)
{
	if (!is_wall(cub3d->cam.p_x - (cub3d->cam.pd_x * cub3d->cam.move_speed),
			cub3d->cam.p_y - (cub3d->cam.pd_y * cub3d->cam.move_speed), cub3d))
	{
		cub3d->cam.p_x -= (cub3d->cam.pd_x * cub3d->cam.move_speed);
		cub3d->cam.p_y -= (cub3d->cam.pd_y * cub3d->cam.move_speed);
	}
}
