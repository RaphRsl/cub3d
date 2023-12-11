/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rroussel <rroussel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 15:50:40 by rroussel          #+#    #+#             */
/*   Updated: 2023/12/11 15:55:28 by rroussel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	render_texture_line(t_ray ray, int x, t_cub3d *c, void *texture)
{
	int	y;

	y = -1;
	while (++y < S_HEIGHT)
	{
		if (y < S_HEIGHT / 2)
			c->img.addr[y * SCREEN_WIDTH + x] = c->config->c_color[0] << 16 | \
				c->config->c_color[1] << 8 | c->config->c_color[2];
		else
			c->img.addr[y * SCREEN_WIDTH + x] = c->config->fl_color[0] << 16 | \
				c->config->fl_color[1] << 8 | c->config->fl_color[2];
	}
	y = ray.draw_start - 1;
	while (++y < ray.draw_end && y < S_HEIGHT)
	{
		ray.tex_y = (int)ray.tex_pos & (c->xpm.tex_h - 1);
		if (ray.tex_y < 0)
			ray.tex_y = 0;
		if (ray.tex_y >= c->xpm.tex_h)
			ray.tex_y = c->xpm.tex_h - 1;
		ray.color = (int *)texture;
		c->img.addr[y * SCREEN_WIDTH + x] = ray.color[ray.tex_y * \
		c->xpm.tex_w + ray.tex_x];
		ray.tex_pos += ray.step;
	}
}

void	set_side_dist(t_ray *ray, t_cub3d *cub3d)
{
	if (ray->ray_dir_x < 0)
	{
		ray->step_x = -1;
		ray->side_dist_x = (cub3d->cam.p_x - ray->map_x) * fabs(1
				/ ray->ray_dir_x);
	}
	else
	{
		ray->step_x = 1;
		ray->side_dist_x = (ray->map_x + 1.0 - cub3d->cam.p_x) * fabs(1
				/ ray->ray_dir_x);
	}
	if (ray->ray_dir_y < 0)
	{
		ray->step_y = -1;
		ray->side_dist_y = (cub3d->cam.p_y - ray->map_y) * fabs(1
				/ ray->ray_dir_y);
	}
	else
	{
		ray->step_y = 1;
		ray->side_dist_y = (ray->map_y + 1.0 - cub3d->cam.p_y) * fabs(1
				/ ray->ray_dir_y);
	}
}

void	set_ray_variables(t_ray *r, t_cub3d *c)
{
	if (r->side == 0)
		r->perp_wall_dist = (r->map_x - c->cam.p_x + (1 - r->step_x) / 2) \
		/ r->ray_dir_x;
	else
		r->perp_wall_dist = (r->map_y - c->cam.p_y + (1 - r->step_y) / 2) \
		/ r->ray_dir_y;
	r->line_height = S_HEIGHT / r->perp_wall_dist;
	r->draw_start = -r->line_height / 2 + S_HEIGHT / 2;
	if (r->draw_start < 0)
		r->draw_start = 0;
	r->draw_end = r->line_height / 2 + S_HEIGHT / 2;
	if (r->draw_end >= S_HEIGHT)
		r->draw_end = S_HEIGHT - 1;
	if (r->side == 0)
		r->wall_x = c->cam.p_y + r->perp_wall_dist * r->ray_dir_y;
	else
		r->wall_x = c->cam.p_x + r->perp_wall_dist * r->ray_dir_x;
	r->wall_x -= floor(r->wall_x);
	r->tex_x = (int)(r->wall_x * (double)c->xpm.tex_w);
	if (r->side == 0 && r->ray_dir_x > 0)
		r->tex_x = c->xpm.tex_w - r->tex_x - 1;
	if (r->side == 1 && r->ray_dir_y < 0)
		r->tex_x = c->xpm.tex_w - r->tex_x - 1;
	r->step = 1.0 * c->xpm.tex_h / r->line_height;
	r->tex_pos = (r->draw_start - S_HEIGHT / 2 + r->line_height / 2) * r->step;
}

void	render_texture_tree(t_ray ray, t_cub3d *cub3d, int x)
{
	if (ray.side == 1 && ray.ray_dir_y > 0)
		render_texture_line(ray, x, cub3d, cub3d->xpm.s_tex_adrr);
	else if (ray.side == 1 && ray.ray_dir_y < 0)
		render_texture_line(ray, x, cub3d, cub3d->xpm.n_tex_adrr);
	else if (ray.side == 0 && ray.ray_dir_x > 0)
		render_texture_line(ray, x, cub3d, cub3d->xpm.e_tex_adrr);
	else
		render_texture_line(ray, x, cub3d, cub3d->xpm.w_tex_adrr);
}

void	ray_side_map(t_ray *ray, t_cub3d *cub3d)
{
	if (ray->side_dist_x < ray->side_dist_y)
	{
		ray->side_dist_x += fabs(1 / ray->ray_dir_x);
		ray->map_x += ray->step_x;
		ray->side = 0;
	}
	else
	{
		ray->side_dist_y += fabs(1 / ray->ray_dir_y);
		ray->map_y += ray->step_y;
		ray->side = 1;
	}
	if (cub3d->config->map[ray->map_y][ray->map_x] > 0
		&& cub3d->config->map[ray->map_y][ray->map_x] < 2)
		ray->hit = 1;
}
