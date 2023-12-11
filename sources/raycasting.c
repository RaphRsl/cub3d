/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsl <rsl@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 16:56:46 by toteixei          #+#    #+#             */
/*   Updated: 2023/12/11 12:57:17 by rsl              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void render_texture_line(int draw_start, int draw_end, int x, double tex_pos, double step, t_cub3d *cub3d, void *texture, int tex_x)
{
    int y = 0;
    int *color = NULL;
    
    while (y < SCREEN_HEIGHT)
    {
        if (y < SCREEN_HEIGHT / 2)
            cub3d->img.addr[y * SCREEN_WIDTH + x] = cub3d->config->c_color[0] << 16 | cub3d->config->c_color[1] << 8 | cub3d->config->c_color[2];
        else
            cub3d->img.addr[y * SCREEN_WIDTH + x] = cub3d->config->fl_color[0] << 16 | cub3d->config->fl_color[1] << 8 | cub3d->config->fl_color[2];
        y++;
    }
    y = draw_start;
    while (y < draw_end && y < SCREEN_HEIGHT)
    {
        int tex_y = (int)tex_pos & (cub3d->xpm.tex_h - 1);
        if (tex_y < 0)
            tex_y = 0;
        if (tex_y >= cub3d->xpm.tex_h)
            tex_y = cub3d->xpm.tex_h - 1;
        color = (int *)texture;
        cub3d->img.addr[y * SCREEN_WIDTH + x] = color[tex_y * cub3d->xpm.tex_w + tex_x];
        tex_pos += step;
        y++;
    }
}

void draw_rays_3d(t_cub3d *cub3d) {
    float pos_x = cub3d->cam.p_x;
    float pos_y = cub3d->cam.p_y;
    float dir_x = cub3d->cam.pd_x;
    float dir_y = cub3d->cam.pd_y;
    int w = SCREEN_WIDTH;
    double fov = cub3d->cam.fov;

    for (int x = 0; x < w; x++) {
        double camera_x = 2 * x / (double)w - 1;
        double ray_angle = atan2(dir_y, dir_x) + fov * (camera_x);

        double ray_dir_x = cos(ray_angle);
        double ray_dir_y = sin(ray_angle);

        int map_x = (int)pos_x;
        int map_y = (int)pos_y;

        double delta_dist_x = fabs(1 / ray_dir_x);
        double delta_dist_y = fabs(1 / ray_dir_y);

        double side_dist_x;
        double side_dist_y;

        double perp_wall_dist;

        int step_x;
        int step_y;
        int hit = 0;
        int side;

        if (ray_dir_x < 0) {
            step_x = -1;
            side_dist_x = (pos_x - map_x) * delta_dist_x;
        } else {
            step_x = 1;
            side_dist_x = (map_x + 1.0 - pos_x) * delta_dist_x;
        }
        if (ray_dir_y < 0) {
            step_y = -1;
            side_dist_y = (pos_y - map_y) * delta_dist_y;
        } else {
            step_y = 1;
            side_dist_y = (map_y + 1.0 - pos_y) * delta_dist_y;
        }

        while (hit == 0) {
            if (side_dist_x < side_dist_y) {
                side_dist_x += delta_dist_x;
                map_x += step_x;
                side = 0;
            } else {
                side_dist_y += delta_dist_y;
                map_y += step_y;
                side = 1;
            }
            if (cub3d->config->map[map_y][map_x] > 0 && cub3d->config->map[map_y][map_x] < 2)
                hit = 1;
        }

        if (side == 0)
            perp_wall_dist = (map_x - pos_x + (1 - step_x) / 2) / ray_dir_x;
        else
            perp_wall_dist = (map_y - pos_y + (1 - step_y) / 2) / ray_dir_y;

        double line_height = SCREEN_HEIGHT / perp_wall_dist;
        int draw_start = -line_height / 2 + SCREEN_HEIGHT / 2;
        if (draw_start < 0)
            draw_start = 0;
        int draw_end = line_height / 2 + SCREEN_HEIGHT / 2;
        if (draw_end >= SCREEN_HEIGHT)
            draw_end = SCREEN_HEIGHT - 1;

        double wall_x;
        if (side == 0)
            wall_x = pos_y + perp_wall_dist * ray_dir_y;
        else
            wall_x = pos_x + perp_wall_dist * ray_dir_x;
        wall_x -= floor(wall_x);
        int tex_x = (int)(wall_x * (double)cub3d->xpm.tex_w);
        if (side == 0 && ray_dir_x > 0)
            tex_x = cub3d->xpm.tex_w - tex_x - 1;
        if (side == 1 && ray_dir_y < 0)
            tex_x = cub3d->xpm.tex_w - tex_x - 1;

        double step = 1.0 * cub3d->xpm.tex_h / line_height;
        double tex_pos = (draw_start - SCREEN_HEIGHT / 2 + line_height / 2) * step;

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
