/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toteixei <toteixei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 15:19:56 by toteixei          #+#    #+#             */
/*   Updated: 2023/12/05 17:13:41 by toteixei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int	check_missing_argument(t_configuration *config)
{
	if (!config->ea_tex)
		return (ft_printf("Missing element: EA\n"), 0);
	if (!config->no_tex)
		return (ft_printf("Missing element: NO\n"), 0);
	if (!config->so_tex)
		return (ft_printf("Missing element: SO\n"), 0);
	if (!config->we_tex)
		return (ft_printf("Missing element: WE\n"), 0);
	if (!config->fl_color[0] && !config->fl_color[1] && !config->fl_color[2])
		return (ft_printf("Missing element: F\n"), 0);
	if (!config->c_color[0] && !config->c_color[1] && !config->c_color[2])
		return (ft_printf("Missing element: C\n"), 0);
	return (1);
}

int	check_floor_ceiling_color(t_configuration *config)
{
	int	i;

	i = 0;
	while (i < 3)
	{
		if (config->fl_color[i] < 0 || config->fl_color[i] > 255)
			return (ft_printf("Wrong floor color format\n"), 0);
		if (config->c_color[i] < 0 || config->c_color[i] > 255)
			return (ft_printf("Wrong ceiling color format\n"), 0);
		i++;
	}
	return (1);

}

int check_xpm_file(t_configuration *config)
{
	int	fd;

	fd = open(config->ea_tex, O_RDONLY);
	if (fd < 0)
		return (ft_printf("Error\nEA texture file does not exist\n"), 0);
	close(fd);
	fd = open(config->no_tex, O_RDONLY);
	if (fd < 0)
		return (ft_printf("Error\nNO texture file does not exist\n"), 0);
	close(fd);
	fd = open(config->so_tex, O_RDONLY);
	if (fd < 0)
		return (ft_printf("Error\nSO texture file does not exist\n"), 0);
	close(fd);
	fd = open(config->we_tex, O_RDONLY);
	if (fd < 0)
		return (ft_printf("Error\nWE texture file does not exist\n"), 0);
	close(fd);
	return (1);
}

int	check_map(t_configuration *config)
{
	int				i;
	int				j;
	int				**map;

	i = -1;
	j = 0;
	map = NULL;
	if (!find_player(config))
		return (0);
	printf("%d\n", config->n_rows);
	while (++i < config->n_rows)
	{
		j = -1;
		if (!(map = duplicate_map(config)))
			return (0);
		while (++j < config->n_column)
		{
			if (config->map[i][j] == 0 || config->map[i][j] == 3)
			{
				if (!flood_fill(config, map, i, j))
					return (ft_free_int_i(map, config->n_rows), 
						ft_printf("Error\nMap is not closed\n"), 0);
				//ft_free_int_i(map, config->n_rows);
			}
		}
	}
	return (1);
}

int	check_arguments(t_configuration *config)
{
	if (!check_missing_argument(config))
		return (0);
	if (!check_floor_ceiling_color(config))
		return (0);
	if (!check_xpm_file(config))
		return (0);
	if (!check_map(config))
		return (0);
	return (1);
}