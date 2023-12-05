/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   end_program.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toteixei <toteixei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 17:06:49 by toteixei          #+#    #+#             */
/*   Updated: 2023/12/05 18:43:15 by toteixei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void free_texture(t_cub3d *cub3d, void *tex)
{
    if (tex)
	{
        mlx_destroy_image(cub3d->mlx, tex);
    }
}

void free_textures(t_cub3d *cub3d)
{
    free_texture(cub3d, cub3d->xpm.n_tex);
    free_texture(cub3d, cub3d->xpm.s_tex);
    free_texture(cub3d, cub3d->xpm.e_tex);
    free_texture(cub3d, cub3d->xpm.w_tex);
}


int end_program(t_cub3d *cub3d)
{
	if (cub3d->win && cub3d->mlx)
		mlx_destroy_window(cub3d->mlx, cub3d->win);
	if (cub3d->config->map)
		ft_free_int_i(cub3d->config->map, cub3d->config->n_rows);
	if (cub3d->config->no_tex)
		free(cub3d->config->no_tex);
	if (cub3d->config->so_tex)
		free(cub3d->config->so_tex);
	if (cub3d->config->we_tex)
		free(cub3d->config->we_tex);
	if (cub3d->config->ea_tex)
		free(cub3d->config->ea_tex);
	if (cub3d->config)
		free(cub3d->config);
	free_textures(cub3d);
	if (cub3d->mlx)
	{
		mlx_destroy_display(cub3d->mlx);
		mlx_loop_end(cub3d->mlx);
		free(cub3d->mlx);
	}
	exit(0);
	return (0);
}