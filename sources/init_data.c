/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toteixei <toteixei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 09:48:05 by toteixei          #+#    #+#             */
/*   Updated: 2023/12/11 09:48:46 by toteixei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	init_textures_bis(t_cub3d *cub3d)
{
	cub3d->xpm.n_tex_adrr = (int *)mlx_get_data_addr(cub3d->xpm.n_tex,
			&cub3d->img.bpp, &cub3d->img.line_len, &cub3d->img.endian);
	if (!cub3d->xpm.n_tex_adrr)
		return (ft_printf("Error\nMalloc\n"), 0);
	cub3d->xpm.s_tex_adrr = (int *)mlx_get_data_addr(cub3d->xpm.s_tex,
			&cub3d->img.bpp, &cub3d->img.line_len, &cub3d->img.endian);
	if (!cub3d->xpm.s_tex_adrr)
		return (ft_printf("Error\nMalloc\n"), 0);
	cub3d->xpm.e_tex_adrr = (int *)mlx_get_data_addr(cub3d->xpm.e_tex,
			&cub3d->img.bpp, &cub3d->img.line_len, &cub3d->img.endian);
	if (!cub3d->xpm.e_tex_adrr)
		return (ft_printf("Error\nMalloc\n"), 0);
	cub3d->xpm.w_tex_adrr = (int *)mlx_get_data_addr(cub3d->xpm.w_tex,
			&cub3d->img.bpp, &cub3d->img.line_len, &cub3d->img.endian);
	if (!cub3d->xpm.w_tex_adrr)
		return (ft_printf("Error\nMalloc\n"), 0);
	return (1);
}

int	init_textures(t_cub3d *cub3d)
{
	cub3d->xpm.tex_w = 1024;
	cub3d->xpm.tex_h = 1024;
	cub3d->xpm.n_tex = mlx_xpm_file_to_image(cub3d->mlx,
			cub3d->config->no_tex, &(cub3d->xpm.tex_w), &(cub3d->xpm.tex_h));
	if (!cub3d->xpm.n_tex)
		return (ft_printf("Error : Wrong north path texture\n"), 0);
	cub3d->xpm.s_tex = mlx_xpm_file_to_image(cub3d->mlx,
			cub3d->config->so_tex, &(cub3d->xpm.tex_w), &(cub3d->xpm.tex_h));
	if (!cub3d->xpm.s_tex)
		return (ft_printf("Error : Wrong south path texture\n"), 0);
	cub3d->xpm.e_tex = mlx_xpm_file_to_image(cub3d->mlx,
			cub3d->config->we_tex, &(cub3d->xpm.tex_w), &(cub3d->xpm.tex_h));
	if (!cub3d->xpm.e_tex)
		return (ft_printf("Error : Wrong east path texture\n"), 0);
	cub3d->xpm.w_tex = mlx_xpm_file_to_image(cub3d->mlx,
			cub3d->config->ea_tex, &(cub3d->xpm.tex_w), &(cub3d->xpm.tex_h));
	if (!cub3d->xpm.w_tex)
		return (ft_printf("Error : Wrong west path texture\n"), 0);
	return (init_textures_bis(cub3d));
}

void	init_cub3d(t_cub3d *cub3d)
{
	cub3d->config = NULL;
	cub3d->img.mlx = NULL;
	cub3d->img.addr = NULL;
	cub3d->mlx = NULL;
	cub3d->win = NULL;
	cub3d->xpm.n_tex = NULL;
	cub3d->xpm.s_tex = NULL;
	cub3d->xpm.e_tex = NULL;
	cub3d->xpm.w_tex = NULL;
	cub3d->xpm.n_tex_adrr = NULL;
	cub3d->xpm.s_tex_adrr = NULL;
	cub3d->xpm.e_tex_adrr = NULL;
	cub3d->xpm.w_tex_adrr = NULL;
}

int	init_mlx_settings(t_cub3d *cub3d)
{
	cub3d->mlx = mlx_init();
	if (!cub3d->mlx)
		return (ft_printf("Error\nMlx init\n"), 0);
	cub3d->win = mlx_new_window(cub3d->mlx, SCREEN_WIDTH,
			SCREEN_HEIGHT, "Cub3D");
	if (!cub3d->win)
		return (ft_printf("Error\nMlx new window\n"), 0);
	cub3d->img.mlx = mlx_new_image(cub3d->mlx, SCREEN_WIDTH, SCREEN_HEIGHT);
	if (!cub3d->img.mlx)
		return (ft_printf("Error\nMlx image\n"), 0);
	cub3d->img.addr = (int *)mlx_get_data_addr(cub3d->img.mlx,
			&cub3d->img.bpp, &cub3d->img.line_len, &cub3d->img.endian);
	if (!cub3d->img.addr)
		return (ft_printf("Error\nMlx image addr\n"), 0);
	return (1);
}
