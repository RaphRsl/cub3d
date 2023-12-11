/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_file_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rroussel <rroussel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 15:23:31 by toteixei          #+#    #+#             */
/*   Updated: 2023/12/11 16:38:46 by rroussel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int	check_map_limits(t_configuration *config, int i, int j, int **map)
{
	while (++i < config->n_rows)
	{
		j = -1;
		while (++j < config->n_column)
		{
			if (config->map[i][j] == 0 || config->map[i][j] == 3)
			{
				if (!flood_fill(config, map, i, j))
					return (ft_free_int_i(map, config->n_rows),
						ft_putstr_fd("Error\nMap is not closed\n", 2), 0);
			}
		}
	}
	return (1);
}

int	find_player(t_configuration *config)
{
	int	player;
	int	x;
	int	y;

	x = 0;
	y = -1;
	player = 0;
	while (++y < config->n_rows)
	{
		x = -1;
		while (++x < config->n_column)
		{
			if (config->map[y][x] == 3)
			{
				player++;
				config->player_x = x;
				config->player_y = y;
			}
		}
	}
	if (player == 0)
		return (ft_putstr_fd("Error\nPlayer is Missing.\n", 2), 0);
	if (player != 1)
		return (ft_putstr_fd("Error\nThere must be only one player.\n", 2), 0);
	return (1);
}

int	**duplicate_map(t_configuration *config)
{
	int	i;
	int	j;
	int	**map_buffer;

	i = 0;
	j = 0;
	map_buffer = malloc(sizeof(int *) * config->n_rows);
	if (!map_buffer)
		return (NULL);
	while (i < config->n_rows)
	{
		map_buffer[i] = malloc(sizeof(int) * config->n_column);
		if (!map_buffer[i])
			return (ft_free_int_i(map_buffer, i), NULL);
		j = 0;
		while (j < config->n_column)
		{
			map_buffer[i][j] = config->map[i][j];
			j++;
		}
		i++;
	}
	return (map_buffer);
}

int	flood_fill(t_configuration *config, int **map, int y, int x)
{
	if (y < 0 || y >= config->n_rows || x < 0 || x >= config->n_column)
		return (0);
	if (map[y][x] == 1 || map[y][x] == 2)
		return (1);
	map[y][x] = 2;
	if (!flood_fill(config, map, y, x + 1))
		return (0);
	if (!flood_fill(config, map, y, x - 1))
		return (0);
	if (!flood_fill(config, map, y + 1, x))
		return (0);
	if (!flood_fill(config, map, y - 1, x))
		return (0);
	return (1);
}

int	ft_check_file_path(char *file)
{
	int	i;

	i = 0;
	while (file[i])
		i++;
	while (i > 0 && file[i] != '.')
		i--;
	if (ft_strcmp(&file[i], ".cub") != 0)
	{
		ft_putstr_fd("Error\n", 2);
		ft_putstr_fd("Unsupported file, only *.cub file can be loaded.\n", 2);
		return (0);
	}
	return (1);
}
