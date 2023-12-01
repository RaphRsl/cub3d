/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   configuration.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toteixei <toteixei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/25 12:31:00 by toteixei          #+#    #+#             */
/*   Updated: 2023/12/01 09:58:00 by toteixei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

t_configuration *init_config_struct(void)
{
	t_configuration *config;
	
	config = malloc(sizeof(t_configuration));
	if (!config)
		return (NULL);
	config->ea_tex = NULL;
	config->no_tex = NULL;
	config->so_tex = NULL;
	config->we_tex = NULL;
	config->map = NULL;
	config->n_column = 0;
	config->n_rows = 0;
	return (config);
}

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

int	check_map(t_configuration *config)
{
	int				i;
	int				j;
	int				**map;

	i = 0;
	j = 0;
	map = duplicate_map(config);
	find_player(config, &i, &j);
	if (i == config->n_rows)
		return (ft_free_int_i(map, config->n_rows), 
			ft_printf("Error\nNo player in the map\n"), 0);
	map[i][j] = 0;
	if (!flood_fill(config, map, i, j))
		return (ft_free_int_i(map, config->n_rows), 
			ft_printf("Error\nMap is not closed\n"), 0);
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

int	is_element(char *line)
{
	int	i;

	i = 0;
	skip_whitespaces(line, &i);
	if (ft_strncmp(&line[i], "SO ", 3) == 0)
		return (1);
	if (ft_strncmp(&line[i], "WE ", 3) == 0)
		return (1);
	if (ft_strncmp(&line[i], "NO ", 3) == 0)
		return (1);
	if (ft_strncmp(&line[i], "EA ", 3) == 0)
		return (1);
	if (ft_strncmp(&line[i], "F ", 2) == 0)
		return (1);
	if (ft_strncmp(&line[i], "C ", 2) == 0)
		return (1);
	return (0);
}

void	skip_whitespaces(char *line, int *i)
{
	while (ft_iswhitespace(line[*i]))
		(*i)++;
}

void	fill_floor_ceiling_color(int color[3], char *line, int *i)
{
	int	j;
	
	j = 0;
	while (line[*i] && j < 3)
	{
		if (ft_isdigit(line[*i]))
		{
			color[j] = ft_atoi(&line[*i]);
			j++;
			while (ft_isdigit(line[*i]))
				(*i)++;
		}
		else if (line[*i] == ',')
			(*i)++;
		else if (ft_iswhitespace(line[*i]))
			(*i)++;
		else
			return ;
	}
}

int	fill_element_bis(char *line, t_configuration **config, int *i)
{
	if (ft_strncmp(line, "EA ", 3) == 0)
    {
		*i += 2;
		skip_whitespaces(line, i);
		(*config)->ea_tex = ft_strdup(&line[*i]);
		if (!(*config)->ea_tex)
			return (0);
    }
    else if (ft_strncmp(line, "F ", 2) == 0)
    {
        *i += 1;
		skip_whitespaces(line, i);
		fill_floor_ceiling_color((*config)->fl_color, line, i);
		
    }
    else if (ft_strncmp(line, "C ", 2) == 0)
    {
        *i += 1;
		skip_whitespaces(line, i);
		fill_floor_ceiling_color((*config)->c_color, line, i);
    }
	return (1);
}

int fill_element(char *line, t_configuration **config, int *i)
{
    if (ft_strncmp(line, "SO ", 3) == 0)
    {
		*i += 2;
		skip_whitespaces(line, i);
		(*config)->so_tex = ft_strdup(&line[*i]);
		if (!(*config)->so_tex)
			return (0);
    }
    else if (ft_strncmp(line, "WE ", 3) == 0)
    {
		*i += 2;
		skip_whitespaces(line, i);
		(*config)->we_tex = ft_strdup(&line[*i]);
		if (!(*config)->we_tex)
			return (0);
    }
    else if (ft_strncmp(line, "NO ", 3) == 0)
    {
		*i += 2;
		skip_whitespaces(line, i);
		(*config)->no_tex = ft_strdup(&line[*i]);
		if (!(*config)->no_tex)
			return (0);
    }
	else
		return (fill_element_bis(line, config, i));
    return (1);
}

int	is_map(char *line)
{
	int	i;

	i = 0;
	skip_whitespaces(line, &i);
	if (line[i] == '1' || line[i] == '0' || line[i] == 'N' || line[i] == 'S' || line[i] == 'E' || line[i] == 'W')
		return (1);
	return (0);
}

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

int	fill_map(char *line, t_configuration **config)
{
	int	i;
	int	j;
	int	**map;
	
	i = 0;
	j = 0;
	skip_whitespaces(line, &i);
	if (!(*config)->map)
	{
		(*config)->map = malloc(sizeof(int *) * 1);
		if (!(*config)->map)
			return (0);
	}
	else
	{
		map = malloc(sizeof(int *) * ((*config)->n_rows + 1));
		if (!map)
			return (0);
		while (j < (*config)->n_rows)
		{
			map[j] = (*config)->map[j];
			j++;
		}
		free((*config)->map);
		(*config)->map = map;
	}
	(*config)->map[(*config)->n_rows] = malloc(sizeof(int) * ft_strlen(&line[i]));
	if (!(*config)->map[(*config)->n_rows])
		return (0);
	j = 0;
	while (line[i])
	{
		if (line[i] == '1' || line[i] == '0' || line[i] == 'N' || line[i] == 'S' || line[i] == 'E' || line[i] == 'W')
		{
			if (line[i] == '1' || line[i] == '0')
				(*config)->map[(*config)->n_rows][j] = line[i] - 48;
			else
			{
				(*config)->map[(*config)->n_rows][j] = 3;
				(*config)->orientation = line[i];
			}
			j++;
		}
		i++;
	}
	(*config)->n_column = j;
	(*config)->n_rows++;
	return (1);
}

int	parse_line(char *line, t_configuration **config)
{
	int	i;
	
	i = -1;
	while (line[++i])
	{
		while (ft_iswhitespace(line[i]))
			i++;
		if (is_element(&line[i]))
		{
				if (!fill_element(&line[i], config, &i))
				return (0);
			else
				return (1);
		}
		else if (is_map(&line[i]))
		{
			if (!fill_map(&line[i], config))
				return (0);
			else
				return (1);
		}
	}
	return (1);
}

t_configuration	*fill_configuration_argument(char **file)
{
	int				i;
	t_configuration *config;
	
	i = 0;
	config = init_config_struct();
	if (!config)
		return (NULL);
	while (file[i])
	{
		if (!parse_line(file[i], &config))
			return (ft_printf("error\n"), NULL); // ne pas oublier d'implementer la liberation de memoire de la structure;
		i++;
	}
	if (!check_arguments(config))
		return (NULL);
	return (config);
}

t_configuration	*parse_map(int fd)
{
	char			*file_in_line;
	char			**file;
	char			*buffer;
	t_configuration	*config;

	file_in_line = NULL;
	buffer = get_next_line(fd);
	if (!*buffer)
		return (0);
	while (buffer)
	{
		file_in_line = ft_strjoin(file_in_line, buffer);
		if (!file_in_line)
			return (free(buffer), NULL);
		free(buffer);
		buffer = get_next_line(fd);
		if (!buffer)
			break ;
	}
	free(buffer);
	close(fd);
	file = ft_split(file_in_line, '\n');
	if (!file)
		return (close(fd), free(file_in_line), ft_printf("Malloc error\n"), NULL);
	config = fill_configuration_argument(file);
	return (close(fd), free(file_in_line), ft_free_arrays_i(file, -1), config);
}

t_configuration	*ft_configuration(char *file_path)
{
	int fd_ptr;

	if (!ft_check_file_path(file_path))
		return (NULL);
	fd_ptr = open(file_path, O_RDONLY);
	if (fd_ptr < 0)
		return (ft_printf("Error\n%s : file does not exist\n", file_path), NULL);
	return (parse_map(fd_ptr));
}