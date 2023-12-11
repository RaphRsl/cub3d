/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsl <rsl@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 16:56:46 by toteixei          #+#    #+#             */
/*   Updated: 2023/12/11 14:11:11 by rsl              ###   ########.fr       */
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


void    init_ray(t_ray *ray, t_cub3d *cub3d, int x)
{
    ray->ray_dir_x = cos(atan2(cub3d->cam.pd_y, cub3d->cam.pd_x) + cub3d->cam.fov * (2 * x / (double)SCREEN_WIDTH - 1));
    ray->ray_dir_y = sin(atan2(cub3d->cam.pd_y, cub3d->cam.pd_x) + cub3d->cam.fov * (2 * x / (double)SCREEN_WIDTH - 1));
    ray->map_x = cub3d->cam.p_x;
    ray->map_y = cub3d->cam.p_y;
    ray->side_dist_x = 0;
    ray->side_dist_y = 0;
    ray->perp_wall_dist = 0;
    ray->step_x = 0;
    ray->step_y = 0;
    ray->hit = 0;
    ray->side = 0;
    ray->line_height = 0;
    ray->draw_start = 0;
    ray->draw_end = 0;
}

void    set_side_dist(t_ray *ray, t_cub3d *cub3d)
{
    if (ray->ray_dir_x < 0)
    {
        ray->step_x = -1;
        ray->side_dist_x = (cub3d->cam.p_x - ray->map_x) * fabs(1 / ray->ray_dir_x);
    }
    else
    {
        ray->step_x = 1;
        ray->side_dist_x = (ray->map_x + 1.0 - cub3d->cam.p_x) * fabs(1 / ray->ray_dir_x);
    }
    if (ray->ray_dir_y < 0)
    {
        ray->step_y = -1;
        ray->side_dist_y = (cub3d->cam.p_y - ray->map_y) * fabs(1 / ray->ray_dir_y);
    }
    else
    {
        ray->step_y = 1;
        ray->side_dist_y = (ray->map_y + 1.0 - cub3d->cam.p_y) * fabs(1 / ray->ray_dir_y);
    }
}

void    set_perp_wall_dist_line_height_draw_start_end(t_ray *ray, t_cub3d *cub3d)
{
    if (ray->side == 0)
        ray->perp_wall_dist = (ray->map_x - cub3d->cam.p_x + (1 - ray->step_x) / 2) / ray->ray_dir_x;
    else
        ray->perp_wall_dist = (ray->map_y - cub3d->cam.p_y + (1 - ray->step_y) / 2) / ray->ray_dir_y;
    ray->line_height = SCREEN_HEIGHT / ray->perp_wall_dist;
    ray->draw_start = -ray->line_height / 2 + SCREEN_HEIGHT / 2;
    if (ray->draw_start < 0)
        ray->draw_start = 0;
    ray->draw_end = ray->line_height / 2 + SCREEN_HEIGHT / 2;
    if (ray->draw_end >= SCREEN_HEIGHT)
        ray->draw_end = SCREEN_HEIGHT - 1;
}

void draw_rays_3d(t_cub3d *cub3d)
{
    t_ray ray;
    int x;

    x = 0;
    while (x < SCREEN_WIDTH)
    {
        init_ray(&ray, cub3d, x);
        set_side_dist(&ray, cub3d);
        while (ray.hit == 0) {
            if (ray.side_dist_x < ray.side_dist_y) {
                ray.side_dist_x += fabs(1 / ray.ray_dir_x);
                ray.map_x += ray.step_x;
                ray.side = 0;
            } else {
                ray.side_dist_y += fabs(1 / ray.ray_dir_y);
                ray.map_y += ray.step_y;
                ray.side = 1;
            }
            if (cub3d->config->map[ray.map_y][ray.map_x] > 0 && cub3d->config->map[ray.map_y][ray.map_x] < 2)
                ray.hit = 1;
        }
        set_perp_wall_dist_line_height_draw_start_end(&ray, cub3d);
        double wall_x;
        if (ray.side == 0)
            wall_x = cub3d->cam.p_y + ray.perp_wall_dist * ray.ray_dir_y;
        else
            wall_x = cub3d->cam.p_x + ray.perp_wall_dist * ray.ray_dir_x;
        wall_x -= floor(wall_x);
        int tex_x = (int)(wall_x * (double)cub3d->xpm.tex_w);
        if (ray.side == 0 && ray.ray_dir_x > 0)
            tex_x = cub3d->xpm.tex_w - tex_x - 1;
        if (ray.side == 1 && ray.ray_dir_y < 0)
            tex_x = cub3d->xpm.tex_w - tex_x - 1;

        double step = 1.0 * cub3d->xpm.tex_h / ray.line_height;
        double tex_pos = (ray.draw_start - SCREEN_HEIGHT / 2 + ray.line_height / 2) * step;

        if (ray.side == 1 && ray.ray_dir_y > 0)
            render_texture_line(ray.draw_start, ray.draw_end, x, tex_pos, step, cub3d, cub3d->xpm.s_tex_adrr, tex_x);
        else if (ray.side == 1 && ray.ray_dir_y < 0)
            render_texture_line(ray.draw_start, ray.draw_end, x, tex_pos, step, cub3d, cub3d->xpm.n_tex_adrr, tex_x);
        else if (ray.side == 0 && ray.ray_dir_x > 0)
            render_texture_line(ray.draw_start, ray.draw_end, x, tex_pos, step, cub3d, cub3d->xpm.e_tex_adrr, tex_x);
        else
            render_texture_line(ray.draw_start, ray.draw_end, x, tex_pos, step, cub3d, cub3d->xpm.w_tex_adrr, tex_x);
        x++;
    }
}
