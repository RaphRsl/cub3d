/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toteixei <toteixei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/25 12:12:55 by toteixei          #+#    #+#             */
/*   Updated: 2023/12/04 16:15:45 by toteixei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	init_textures(t_cub3d *cub3d)
{
	cub3d->xpm.tex_width = 64;
	cub3d->xpm.tex_height = 64;
	if (!(cub3d->xpm.n_tex = mlx_xpm_file_to_image(cub3d->mlx, cub3d->config->no_tex, &(cub3d->xpm.tex_width), &(cub3d->xpm.tex_height))))
	{
		printf("Error : Wrong north path texture\n");
		return (0);
	}
	if (!(cub3d->xpm.s_tex = mlx_xpm_file_to_image(cub3d->mlx, cub3d->config->so_tex, &(cub3d->xpm.tex_width), &(cub3d->xpm.tex_height))))
	{
		printf("Error : Wrong south path texture\n");
		return (0);
	}
	if (!(cub3d->xpm.e_tex = mlx_xpm_file_to_image(cub3d->mlx, cub3d->config->we_tex, &(cub3d->xpm.tex_width), &(cub3d->xpm.tex_height))))
	{
		printf("Error : Wrong east path texture\n");
		return (0);
	}
	if (!(cub3d->xpm.w_tex = mlx_xpm_file_to_image(cub3d->mlx, cub3d->config->ea_tex, &(cub3d->xpm.tex_width), &(cub3d->xpm.tex_height))))
	{
		printf("Error : Wrong west path texture\n");
		return (0);
	}
	cub3d->xpm.n_tex = mlx_get_data_addr(cub3d->xpm.n_tex, &cub3d->img.bpp, &cub3d->img.line_len, &cub3d->img.endian);
	cub3d->xpm.s_tex = mlx_get_data_addr(cub3d->xpm.s_tex, &cub3d->img.bpp, &cub3d->img.line_len, &cub3d->img.endian);
	cub3d->xpm.e_tex = mlx_get_data_addr(cub3d->xpm.e_tex, &cub3d->img.bpp, &cub3d->img.line_len, &cub3d->img.endian);
	cub3d->xpm.w_tex = mlx_get_data_addr(cub3d->xpm.w_tex, &cub3d->img.bpp, &cub3d->img.line_len, &cub3d->img.endian);
	return (1);
}

void	init_cam_settings(t_cub3d *cub3d)
{
	cub3d->cam.p_x = cub3d->config->player_x + 0.5;
	cub3d->cam.p_y = cub3d->config->player_y + 0.5;
	if (cub3d->config->orientation == 'E')
		cub3d->cam.pa = 0;
	else if (cub3d->config->orientation == 'W')
		cub3d->cam.pa = M_PI;
	else if (cub3d->config->orientation == 'N')
		cub3d->cam.pa = 2 * M_PI - M_PI / 2;
	else if (cub3d->config->orientation == 'S')
		cub3d->cam.pa = M_PI / 2;
	cub3d->cam.pd_x = cos(cub3d->cam.pa) * 5;
	cub3d->cam.pd_y = sin(cub3d->cam.pa) * 5;
	cub3d->cam.fov = 60;
}


int	main(int argc, char **argv)
{
	t_cub3d			cub3d;

	if (argc != 2)
		return (1);
	cub3d.config = ft_configuration(argv[1]);
	if (!cub3d.config)
		return (1);
	init_cam_settings(&cub3d);
	cub3d.mlx = mlx_init();
	cub3d.win = mlx_new_window(cub3d.mlx, SCREEN_WIDTH + 5, SCREEN_HEIGTH + 5, "Cub3D");
	cub3d.img.mlx = mlx_new_image(cub3d.mlx, SCREEN_WIDTH, SCREEN_HEIGTH);
	cub3d.img.addr = (int *)mlx_get_data_addr(cub3d.img.mlx, &cub3d.img.bpp, &cub3d.img.line_len, &cub3d.img.endian);
	if (!init_textures(&cub3d))
		return (1); // liberer le reste de la memoire
	mlx_loop_hook(cub3d.mlx, &ft_render_game, &cub3d);
	mlx_hook(cub3d.win, ON_DESTROY, ON_DESTROY, end_program, &cub3d);
	mlx_hook(cub3d.win, 2, 1L << 0, deal_key, &cub3d);
	mlx_loop(cub3d.mlx);
	return (0);
}