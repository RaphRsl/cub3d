/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rroussel <rroussel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 16:56:46 by toteixei          #+#    #+#             */
/*   Updated: 2023/12/11 15:55:18 by rroussel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	init_ray(t_ray *ray, t_cub3d *cub3d, int x)
{
	ray->ray_dir_x = cos(atan2(cub3d->cam.pd_y, cub3d->cam.pd_x)
			+ cub3d->cam.fov * (2 * x / (double)SCREEN_WIDTH - 1));
	ray->ray_dir_y = sin(atan2(cub3d->cam.pd_y, cub3d->cam.pd_x)
			+ cub3d->cam.fov * (2 * x / (double)SCREEN_WIDTH - 1));
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
	ray->color = NULL;
	ray->wall_x = 0;
	ray->tex_x = 0;
	ray->tex_y = 0;
	ray->step = 0;
	ray->tex_pos = 0;
}

void	draw_rays_3d(t_cub3d *cub3d)
{
	t_ray	ray;
	int		x;

	x = 0;
	while (x < SCREEN_WIDTH)
	{
		init_ray(&ray, cub3d, x);
		set_side_dist(&ray, cub3d);
		while (ray.hit == 0)
			ray_side_map(&ray, cub3d);
		set_ray_variables(&ray, cub3d);
		render_texture_tree(ray, cub3d, x);
		x++;
	}
}
