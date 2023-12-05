/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera_movement.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rroussel <rroussel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 15:03:44 by toteixei          #+#    #+#             */
/*   Updated: 2023/12/05 16:10:28 by rroussel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int is_wall(float x, float y, t_cub3d *cub3d)
{
    if (cub3d->config->map[(int)y][(int)x] == 1)
        return (1);
    return (0);
}

//TOM CODE
// void	rotate_left(t_camera *cam)
// {
//     cam->pa -= 0.05;
//     if (cam->pa < 1 * M_PI) //was 0
//         cam->pa += 2 * M_PI;
//     cam->pd_x = cos(cam->pa) * cam->rot_speed;
//     cam->pd_y = sin(cam->pa) * cam->rot_speed;
// }

//TOM CODE
// void    rotate_right(t_camera *cam)
// {
//     cam->pa += 0.05;
//     if (cam->pa > 2 * M_PI)
//         cam->pa -= 2 * M_PI;
//     cam->pd_x = cos(cam->pa) * cam->rot_speed;
//     cam->pd_y = sin(cam->pa) * cam->rot_speed;
// }


void rotate_left(t_camera *cam)
{
    double old_pd_x = cam->pd_x;
    double old_plane_x = cam->plane_x;

    cam->pd_x = cam->pd_x * cos(-cam->rot_speed) - cam->pd_y * sin(-cam->rot_speed);
    cam->pd_y = old_pd_x * sin(-cam->rot_speed) + cam->pd_y * cos(-cam->rot_speed);

    cam->plane_x = cam->plane_x * cos(-cam->rot_speed) - cam->plane_y * sin(-cam->rot_speed);
    cam->plane_y = old_plane_x * sin(-cam->rot_speed) + cam->plane_y * cos(-cam->rot_speed);

    cam->pa -= cam->rot_speed;
    if (cam->pa < 0)
        cam->pa += 2 * M_PI;
}


void rotate_right(t_camera *cam)
{
    double old_pd_x = cam->pd_x;
    double old_plane_x = cam->plane_x;

    // first we need to upfate direction vectors using matrix multiplication, eqsier than using trigonometry
    cam->pd_x = cam->pd_x * cos(cam->rot_speed) - cam->pd_y * sin(cam->rot_speed);
    cam->pd_y = old_pd_x * sin(cam->rot_speed) + cam->pd_y * cos(cam->rot_speed);

    // same thing for the plane vectors, also using matrix multiplication
    cam->plane_x = cam->plane_x * cos(cam->rot_speed) - cam->plane_y * sin(cam->rot_speed);
    cam->plane_y = old_plane_x * sin(cam->rot_speed) + cam->plane_y * cos(cam->rot_speed);
    
    // then  i update the rotation angle using PI
    cam->pa += cam->rot_speed;
    if (cam->pa > 2 * M_PI)
        cam->pa -= 2 * M_PI;
}


void    move_to_the_right(t_cub3d *cub3d)
{
    if (!is_wall(cub3d->cam.p_x + (cub3d->cam.pd_x * 0.1), cub3d->cam.p_y + (cub3d->cam.pd_y * 0.1), cub3d))
    {   
    cub3d->cam.p_x -= (cub3d->cam.pd_y * cub3d->cam.move_speed);
    cub3d->cam.p_y += (cub3d->cam.pd_x * cub3d->cam.move_speed);
    }
}

void    move_to_the_left(t_cub3d *cub3d)
{
    if(!is_wall(cub3d->cam.p_x + (cub3d->cam.pd_y * 0.1), cub3d->cam.p_y - (cub3d->cam.pd_x * 0.1), cub3d))
    {
    cub3d->cam.p_x += (cub3d->cam.pd_y * cub3d->cam.move_speed);
    cub3d->cam.p_y -= (cub3d->cam.pd_x * cub3d->cam.move_speed);
    }
}

void    move_forward(t_cub3d *cub3d)
{
    if (!is_wall(cub3d->cam.p_x + (cub3d->cam.pd_x * 0.1), cub3d->cam.p_y + (cub3d->cam.pd_y * 0.1), cub3d))
    {   
        cub3d->cam.p_x += (cub3d->cam.pd_x * cub3d->cam.move_speed);
        cub3d->cam.p_y += (cub3d->cam.pd_y * cub3d->cam.move_speed);
    }
}

void    move_backward(t_cub3d *cub3d)
{
   if (!is_wall(cub3d->cam.p_x - (cub3d->cam.pd_x * 0.1), cub3d->cam.p_y - (cub3d->cam.pd_y * 0.1), cub3d))
    {
        cub3d->cam.p_x -= (cub3d->cam.pd_x * cub3d->cam.move_speed);
        cub3d->cam.p_y -= (cub3d->cam.pd_y * cub3d->cam.move_speed);
    }
}