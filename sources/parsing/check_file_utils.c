/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_file_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toteixei <toteixei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 15:23:31 by toteixei          #+#    #+#             */
/*   Updated: 2023/12/05 15:29:10 by toteixei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	print_map(t_configuration *config)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (i < config->n_rows)
	{
		j = 0;
		while (j < config->n_column)
		{
			ft_printf("%d, ", config->map[i][j]);
			j++;
		}
		ft_printf("\n");
		i++;
	}
}

void	find_player(t_configuration *config, int *i, int *j)
{
	while (*i < config->n_rows)
	{
		*j = 0;
		while (*j < config->n_column)
		{
			if (config->map[*i][*j] == 3)
			{
				config->player_x = *j;
				config->player_y = *i;
				return ;
			}
			(*j)++;
		}
		(*i)++;
	}
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
