/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toteixei <toteixei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 16:56:46 by toteixei          #+#    #+#             */
/*   Updated: 2023/12/05 18:42:15 by toteixei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void    render_texture_line(int draw_start, int draw_end, int x, double tex_pos, double step, t_cub3d *cub3d, int *texture, int tex_x)
{
    int y = 0;
    int *color = 0;
    while (y < draw_start)
    {
        cub3d->img.addr[y * SCREEN_WIDTH + x] = cub3d->config->c_color[0] << 16 | cub3d->config->c_color[1] << 8 | cub3d->config->c_color[2];
        y++;
    }
    while (y < draw_end)
    {
        int tex_y = (int)tex_pos & (cub3d->xpm.tex_height - 1);
        tex_pos += step;
        color = texture;
        cub3d->img.addr[y * SCREEN_WIDTH + x] = color[tex_y * cub3d->xpm.tex_height + tex_x];
        y++;
    }
    while (y < SCREEN_HEIGTH)
    {
        cub3d->img.addr[y * SCREEN_WIDTH + x] = cub3d->config->fl_color[0] << 16 | cub3d->config->fl_color[1] << 8 | cub3d->config->fl_color[2];
        y++;
    }
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
        
        double wall_x;
        if (side == 0)
            wall_x = pos_y + perp_wall_dist * ray_dir_y;
        else
            wall_x = pos_x + perp_wall_dist * ray_dir_x;
        wall_x -= floor(wall_x);
        int tex_x = (int)(wall_x * (double)cub3d->xpm.tex_width);
        if (side == 0 && ray_dir_x > 0)
            tex_x = cub3d->xpm.tex_width - tex_x - 1;
        if (side == 1 && ray_dir_y < 0)
            tex_x = cub3d->xpm.tex_width - tex_x - 1;
        double step = 1.0 * cub3d->xpm.tex_height / line_height;
        double tex_pos = (draw_start - SCREEN_HEIGTH / 2 + line_height / 2) * step;
        if (side == 1 && ray_dir_y > 0)
            render_texture_line(draw_start, draw_end, x, tex_pos, step, cub3d, cub3d->xpm.s_tex_adrr, tex_x);
        else if (side == 1 && ray_dir_y < 0)
            render_texture_line(draw_start, draw_end, x, tex_pos, step, cub3d, cub3d->xpm.n_tex_adrr, tex_x);
        else if (side == 0 && ray_dir_x > 0)
            render_texture_line(draw_start, draw_end, x, tex_pos, step, cub3d, cub3d->xpm.e_tex_adrr, tex_x);
        else
            render_texture_line(draw_start, draw_end, x, tex_pos, step, cub3d, cub3d->xpm.w_tex_adrr, tex_x);
    }
}

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