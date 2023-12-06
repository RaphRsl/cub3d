/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_file_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toteixei <toteixei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 15:23:31 by toteixei          #+#    #+#             */
/*   Updated: 2023/12/06 13:29:48 by toteixei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	print_map(t_configuration *confi, int **map)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	printf("n_rows: %d\n", confi->n_rows);
	printf("n_column: %d\n", confi->n_column);
	while (i < confi->n_rows)
	{
		j = 0;
		while (j < confi->n_column)
		{
			ft_printf("%d, ", map[i][j]);
			j++;
		}
		ft_printf("\n");
		i++;
	}
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
	if (player != 1)
		return (ft_printf("Error\nThere must be only one player.\n"), 0);
	return (1);
}

// int	find_player(t_configuration *config, int *i, int *j)
// {
// 	int	player;
// 	int	x;
// 	int	y;

// 	x = 0;
// 	y = -1;
// 	player = 0;
// 	while (++y < config->n_rows)
// 	{
// 		x = -1;
// 		while (++x < config->n_column)
// 		{
// 			if (config->map[y][x] == 3)
// 			{
// 				player++;
// 				config->player_x = x;
// 				config->player_y = y;
// 				*i = y;
// 				*j = x;
// 			}
// 		}
// 	}
// 	if (player != 1)
// 		return (ft_printf("Error\nThere must be only one player.\n"), 0);
// 	return (1);
// }

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

int flood_fill(t_configuration *config, int **map, int y, int x)
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
		ft_printf("Error\n");
		ft_printf("Unsupported file, only *.cub file can be loaded.\n");
		return (0);
	}
	return (1);
}
