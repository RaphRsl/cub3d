/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rroussel <rroussel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/08 16:14:36 by toteixei          #+#    #+#             */
/*   Updated: 2023/12/11 15:46:59 by rroussel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	print_a_square(t_minimap m, int color, t_cub3d *cub3d)
{
	int	x;
	int	y;

	x = m.scr_x;
	while (x < m.scr_x + m.bs)
	{
		y = m.scr_y;
		while (y < m.scr_y + m.bs)
		{
			img_pixel_put(x, y, color, cub3d);
			y++;
		}
		x++;
	}
}

void	print_direction_line_of_player(t_cub3d *cub3d)
{
	t_point	player;
	t_point	direction;

	player.x = SCREEN_WIDTH / 8 + 5;
	player.y = S_HEIGHT / 8 + 5;
	player.color = 0x00FF0000;
	direction.x = player.x + (cub3d->cam.pd_x * 10);
	direction.y = player.y + (cub3d->cam.pd_y * 10);
	draw_line(cub3d, player, direction);
}

void	put_wall_floor_square(t_cub3d *cub3d, t_minimap m)
{
	if (cub3d->config->map[m.y][m.x] == 1)
		print_a_square(m, 0x000000, cub3d);
	else
		print_a_square(m, 0xFFFFFF, cub3d);
}

void	init_minimap(t_minimap *m, t_cub3d *cub3d)
{
	m->bs = 10;
	m->player_screen_x = SCREEN_WIDTH / 8;
	m->player_screen_y = S_HEIGHT / 8;
	m->start_x = m->player_screen_x - 15 * m->bs;
	m->end_x = m->player_screen_x + 15 * m->bs;
	m->start_y = m->player_screen_y - 10 * m->bs;
	m->end_y = m->player_screen_y + 10 * m->bs;
	m->player_map_x = (int)fabs(cub3d->cam.p_x);
	m->player_map_y = (int)fabs(cub3d->cam.p_y);
	m->scr_y = m->start_y;
	m->scr_x = m->start_x;
	m->x = 0;
	m->y = 0;
	m->n_col = cub3d->config->n_column;
	m->n_row = cub3d->config->n_rows;
}

void	ft_print_map(t_cub3d *cub3d)
{
	t_minimap	m;

	init_minimap(&m, cub3d);
	while (m.scr_y < m.end_y)
	{
		m.y = m.player_map_y - 10 + (m.scr_y - m.start_y) / m.bs;
		m.scr_x = m.start_x;
		while (m.scr_x < m.end_x)
		{
			m.x = m.player_map_x - 15 + (m.scr_x - m.start_x) / m.bs;
			if (m.x >= 0 && m.x < m.n_col && m.y >= 0 && m.y < m.n_row)
				put_wall_floor_square(cub3d, m);
			else
				print_a_square(m, 0x000000, cub3d);
			m.scr_x += m.bs;
		}
		m.scr_y += m.bs;
	}
	m.scr_x = SCREEN_WIDTH / 8;
	m.scr_y = S_HEIGHT / 8;
	print_a_square(m, 0xFF0000, cub3d);
	print_direction_line_of_player(cub3d);
}
