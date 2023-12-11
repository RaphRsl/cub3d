/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rroussel <rroussel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 15:19:56 by toteixei          #+#    #+#             */
/*   Updated: 2023/12/11 16:34:53 by rroussel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int	check_missing_argument(t_configuration *config)
{
	if (!config->ea_tex)
		return (ft_putstr_fd("Error\nMissing texture element\n", 2), 0);
	if (!config->no_tex)
		return (ft_putstr_fd("Error\nMissing texture element\n", 2), 0);
	if (!config->so_tex)
		return (ft_putstr_fd("Error\nMissing texture element\n", 2), 0);
	if (!config->we_tex)
		return (ft_putstr_fd("Error\nMissing texture element\n", 2), 0);
	if (config->fl_color[0] < 0 && config->fl_color[1] < 0
		&& config->fl_color[2] < 0)
		return (ft_putstr_fd("Error\nF : Missing element or negative \
		value\n", 2), 0);
	if (config->c_color[0] < 0 && config->c_color[1] < 0
		&& config->c_color[2] < 0)
		return (ft_putstr_fd("Error\nC : Missing element or negative \
		value\n", 2), 0);
	if (!config->map)
		return (ft_putstr_fd("Error\nMap Missing\n", 2), 0);
	return (1);
}

int	check_floor_ceiling_color(t_configuration *config)
{
	int	i;

	i = 0;
	while (i < 3)
	{
		if (config->fl_color[i] < 0 || config->fl_color[i] > 255)
			return (ft_putstr_fd("Error\nWrong floor color format\n", 2), 0);
		if (config->c_color[i] < 0 || config->c_color[i] > 255)
			return (ft_putstr_fd("Error\nWrong ceiling color format\n", 2), 0);
		i++;
	}
	return (1);
}

int	check_xpm_file(t_configuration *config)
{
	int	fd;

	fd = open(config->ea_tex, O_RDONLY);
	if (fd < 0)
		return (ft_putstr_fd("Error\nEA texture file does not exist\n", 2), 0);
	close(fd);
	fd = open(config->no_tex, O_RDONLY);
	if (fd < 0)
		return (ft_putstr_fd("Error\nNO texture file does not exist\n", 2), 0);
	close(fd);
	fd = open(config->so_tex, O_RDONLY);
	if (fd < 0)
		return (ft_putstr_fd("Error\nSO texture file does not exist\n", 2), 0);
	close(fd);
	fd = open(config->we_tex, O_RDONLY);
	if (fd < 0)
		return (ft_putstr_fd("Error\nWE texture file does not exist\n", 2), 0);
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
	map = duplicate_map(config);
	if (!map)
		return (0);
	if (!check_map_limits(config, i, j, map))
		return (0);
	ft_free_int_i(map, config->n_rows);
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
