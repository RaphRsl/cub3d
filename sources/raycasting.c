/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rroussel <rroussel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 16:56:46 by toteixei          #+#    #+#             */
/*   Updated: 2023/12/04 14:10:45 by rroussel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int     chose_depth_color(int color, int line_heigth)
{   
    float   assombrissement;
    int     r;
    int     g;
    int     b;
    
    r = (color & 0x00FF0000) >> 16;
    g = (color & 0x0000FF00) >> 8;
    b = (color & 0x000000FF);
    assombrissement = (float)line_heigth / (float)SCREEN_HEIGTH;
    r = (int)((float)r * assombrissement);
    g = (int)((float)g * assombrissement);
    b = (int)((float)b * assombrissement);
    color = (r << 16) + (g << 8) + b;

    return (color);
}

void    draw_ray(t_cub3d *cub3d, float rx, float ry)
{
    t_point player;
    t_point ray;
    
    player.x = 100 + (cub3d->cam.p_x * 20);
    player.y = 100 + (cub3d->cam.p_y * 20);
    ray.x = 100 + (rx * 20);
    ray.y = 100 + (ry * 20);
    draw_line(cub3d, player, ray);
}



void    draw_rays_3d(t_cub3d *cub3d)
{
    float   pos_x = cub3d->cam.p_x;
    float   pos_y = cub3d->cam.p_y;
    float   dir_x = cub3d->cam.pd_x;
    float   dir_y = cub3d->cam.pd_y;
    float   plane_x = cub3d->cam.plane_x;
    float   plane_y = cub3d->cam.plane_y;
    int     w = SCREEN_WIDTH;
    int     x = 0;

    while (x++ < w)
    {
        double camera_x = 2 * x / (double)w - 1;
        double ray_dir_x = dir_x + plane_x * camera_x;
        double ray_dir_y = dir_y + plane_y * camera_x;
        int map_x = (int)pos_x;
        int map_y = (int)pos_y;

        //distance de la position actuelle du joueur au prochain x ou y
        double side_dist_x;
        double side_dist_y;
        
        double delta_dist_x = sqrt(1 + (ray_dir_y * ray_dir_y) / (ray_dir_x * ray_dir_x));
        double delta_dist_y = sqrt(1 + (ray_dir_x * ray_dir_x) / (ray_dir_y * ray_dir_y));
        double perp_wall_dist;
        int step_x;
        int step_y;
        int hit = 0;
        int side;
        if (ray_dir_x < 0)
        {
            step_x = -1;
            side_dist_x = (pos_x - map_x) * delta_dist_x;
        }
        else
        {
            step_x = 1;
            side_dist_x = (map_x + 1.0 - pos_x) * delta_dist_x;
        }
        if (ray_dir_y < 0)
        {
            step_y = -1;
            side_dist_y = (pos_y - map_y) * delta_dist_y;
        }
        else
        {
            step_y = 1;
            side_dist_y = (map_y + 1.0 - pos_y) * delta_dist_y;
        }
        while (hit == 0)
        {
            if (side_dist_x < side_dist_y)
            {
                side_dist_x += delta_dist_x;
                map_x += step_x;
                side = 0;
            }
            else
            {
                side_dist_y += delta_dist_y;
                map_y += step_y;
                side = 1;
            }
            if (cub3d->config->map[map_y][map_x] > 0 && cub3d->config->map[map_y][map_x] < 2)
                hit = 1;
        }
        if (side == 0)
            perp_wall_dist = (side_dist_x - delta_dist_x);
        else
            perp_wall_dist = (side_dist_y - delta_dist_y);
        int line_height = (int)(SCREEN_HEIGTH / perp_wall_dist);
        int draw_start = -line_height / 2 + SCREEN_HEIGTH / 2;
        if (draw_start < 0)
            draw_start = 0;
        int draw_end = line_height / 2 + SCREEN_HEIGTH / 2;
        if (draw_end >= SCREEN_HEIGTH)
            draw_end = SCREEN_HEIGTH - 1;
        int color = chose_depth_color(0x0000FF000, line_height);
        if (side == 1 && ray_dir_y > 0)
            color = chose_depth_color(0x00FF0000, line_height);
        else if (side == 1 && ray_dir_y < 0)
            color = chose_depth_color(0x000000FF, line_height);
        else if (side == 0 && ray_dir_x > 0)
            color = chose_depth_color(0x0000FF00, line_height);
        else
            color = 0x00FFFF00;
        draw_line(cub3d, (t_point){x, draw_start, 0, color}, (t_point){x, draw_end, 0, color});
    }
}



// -------- PREVIOUS TOM FUNCTION --------
// void    draw_rays_3d(t_cub3d *cub3d)
// {
//     float   pos_x = cub3d->cam.p_x;
//     float   pos_y = cub3d->cam.p_y;
//     float   dir_x = cub3d->cam.pd_x;
//     float   dir_y = cub3d->cam.pd_y;
//     float   plane_x = 0;
//     float   plane_y = 0.66;
//     int     w = SCREEN_WIDTH;
//     int     x = 0;

//     while (x++ < w)
//     {
//         double camera_x = 2 * x / (double)w - 1;
//         double ray_dir_x = dir_x + plane_x * camera_x;
//         double ray_dir_y = dir_y + plane_y * camera_x;
//         int map_x = (int)pos_x;
//         int map_y = (int)pos_y;

//         //distance de la position actuelle du joueur au prochain x ou y
//         double side_dist_x;
//         double side_dist_y;
        
//         double delta_dist_x = sqrt(1 + (ray_dir_y * ray_dir_y) / (ray_dir_x * ray_dir_x));
//         double delta_dist_y = sqrt(1 + (ray_dir_x * ray_dir_x) / (ray_dir_y * ray_dir_y));
//         double perp_wall_dist;
//         int step_x;
//         int step_y;
//         int hit = 0;
//         int side;
//         if (ray_dir_x < 0)
//         {
//             step_x = -1;
//             side_dist_x = (pos_x - map_x) * delta_dist_x;
//         }
//         else
//         {
//             step_x = 1;
//             side_dist_x = (map_x + 1.0 - pos_x) * delta_dist_x;
//         }
//         if (ray_dir_y < 0)
//         {
//             step_y = -1;
//             side_dist_y = (pos_y - map_y) * delta_dist_y;
//         }
//         else
//         {
//             step_y = 1;
//             side_dist_y = (map_y + 1.0 - pos_y) * delta_dist_y;
//         }
//         while (hit == 0)
//         {
//             if (side_dist_x < side_dist_y)
//             {
//                 side_dist_x += delta_dist_x;
//                 map_x += step_x;
//                 side = 0;
//             }
//             else
//             {
//                 side_dist_y += delta_dist_y;
//                 map_y += step_y;
//                 side = 1;
//             }
//             if (cub3d->config->map[map_y][map_x] > 0 && cub3d->config->map[map_y][map_x] < 2)
//                 hit = 1;
//         }
//         if (side == 0)
//             perp_wall_dist = (side_dist_x - delta_dist_x);
//         else
//             perp_wall_dist = (side_dist_y - delta_dist_y);
//         int line_height = (int)(SCREEN_HEIGTH / perp_wall_dist);
//         int draw_start = -line_height / 2 + SCREEN_HEIGTH / 2;
//         if (draw_start < 0)
//             draw_start = 0;
//         int draw_end = line_height / 2 + SCREEN_HEIGTH / 2;
//         if (draw_end >= SCREEN_HEIGTH)
//             draw_end = SCREEN_HEIGTH - 1;
//         int color = chose_depth_color(0x0000FF000, line_height);
//         if (side == 1 && ray_dir_y > 0)
//             color = chose_depth_color(0x00FF0000, line_height);
//         else if (side == 1 && ray_dir_y < 0)
//             color = chose_depth_color(0x000000FF, line_height);
//         else if (side == 0 && ray_dir_x > 0)
//             color = chose_depth_color(0x0000FF00, line_height);
//         else
//             color = 0x00FFFF00;
//         draw_line(cub3d, (t_point){x, draw_start, 0, color}, (t_point){x, draw_end, 0, color});
//     }
// }

// void    draw_rays_3d(t_cub3d *cub3d)
// {
//     int r, mx, my, mp, dof;
//     float rx, ry, ra, xo, yo, aTan;
    
//     ra = cub3d->cam.pa;
//     r = 0;
//     while(r++ < 1)
//     {
//         //only horizontal line
//         dof = 0;
//         aTan = -1 / tan(ra);
//         if (ra > PI)
//         {
//             ry = (((int)cub3d->cam.p_y >> 6) << 6) - 0.0001;
//             printf("ry: %f\n", ry);
//             rx = (cub3d->cam.p_y - ry) * aTan + cub3d->cam.p_x;
//             printf("rx: %f\n", rx);
//             yo = -64;
//             xo = -yo * aTan;
//         }
//         if (ra < PI)
//         {
//             ry = (((int)cub3d->cam.p_y >> 6) << 6) + 64;
//             rx = (cub3d->cam.p_y - ry) * aTan + cub3d->cam.p_x;
//             yo = 64;
//             xo = -yo * aTan;
//         }
//         if (ra == 0)
//         {
//             rx = cub3d->cam.p_x;
//             ry = cub3d->cam.p_y;
//             dof = 8;
//         }
//         while (dof < 8)
//         {
//             mx = (int)(rx) >> 6;
//             my = (int)(ry) >> 6;
            
//             mp = my * cub3d->config->n_column + mx;
//             if (mx < 0 || mx >= cub3d->config->n_column || my < 0 || my >= cub3d->config->n_rows)
//             {
//                 my = 0;
//                 mx = 0;
//             }
//             if ((mp < cub3d->config->n_column * cub3d->config->n_rows) && cub3d->config->map[my][mx] == 1)
//                 dof = 8;
//             else
//             {
//                 rx += xo;
//                 ry += yo;
//                 dof += 1;
//             }
//             draw_ray(cub3d, rx, ry);
//         }
//     }
// }