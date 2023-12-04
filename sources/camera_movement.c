/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera_movement.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rroussel <rroussel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 15:03:44 by toteixei          #+#    #+#             */
/*   Updated: 2023/12/04 14:15:59 by rroussel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int is_wall(float x, float y, t_cub3d *cub3d)
{
    if (cub3d->config->map[(int)y][(int)x] == 1)
        return (1);
    return (0);
}

void	rotate_left(t_camera *cam)
{
    cam->pa -= 0.05;
    if (cam->pa < 0)
        cam->pa += 2 * M_PI;
    cam->pd_x = cos(cam->pa) * 5;
    cam->pd_y = sin(cam->pa) * 5;
}

void    rotate_right(t_camera *cam)
{
    cam->pa += 0.05;
    if (cam->pa > 2 * M_PI)
        cam->pa -= 2 * M_PI;
    cam->pd_x = cos(cam->pa) * 5;
    cam->pd_y = sin(cam->pa) * 5;
}

void    move_forward(t_cub3d *cub3d)
{
    if (!is_wall(cub3d->cam.p_x + (cub3d->cam.pd_x * 0.1), cub3d->cam.p_y + (cub3d->cam.pd_y * 0.1), cub3d))
    {   
        cub3d->cam.p_x += (cub3d->cam.pd_x * 0.1);
        cub3d->cam.p_y += (cub3d->cam.pd_y * 0.1);
    }
}

void    move_backward(t_cub3d *cub3d)
{
   if (!is_wall(cub3d->cam.p_x - (cub3d->cam.pd_x * 0.1), cub3d->cam.p_y - (cub3d->cam.pd_y * 0.1), cub3d))
    {
        cub3d->cam.p_x -= (cub3d->cam.pd_x * 0.1);
        cub3d->cam.p_y -= (cub3d->cam.pd_y * 0.1);
    }
}