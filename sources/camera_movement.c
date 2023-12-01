/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera_movement.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toteixei <toteixei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 15:03:44 by toteixei          #+#    #+#             */
/*   Updated: 2023/12/01 15:11:52 by toteixei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	rotate_left(t_camera *cam)
{
    cam->pa -= 0.1;
    if (cam->pa < 0)
        cam->pa += 2 * M_PI;
    cam->pd_x = cos(cam->pa) * 5;
    cam->pd_y = sin(cam->pa) * 5;
}

void    rotate_right(t_camera *cam)
{
    cam->pa += 0.1;
    if (cam->pa > 2 * M_PI)
        cam->pa -= 2 * M_PI;
    cam->pd_x = cos(cam->pa) * 5;
    cam->pd_y = sin(cam->pa) * 5;
}

void    move_forward(t_camera *cam)
{
    cam->p_x += cam->pd_x;
    cam->p_y += cam->pd_y;
}

void    move_backward(t_camera *cam)
{
    cam->p_x -= cam->pd_x;
    cam->p_y -= cam->pd_y;
}