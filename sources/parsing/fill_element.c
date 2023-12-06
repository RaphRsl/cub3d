/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_element.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toteixei <toteixei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 15:25:49 by toteixei          #+#    #+#             */
/*   Updated: 2023/12/06 17:49:00 by toteixei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int	fill_element_quater(char *line, t_configuration **config, int *i)
{
	if (ft_strncmp(&line[*i], "WE ", 3) == 0)
	{
		if ((*config)->we_tex)
			return (ft_printf("WE key find multiple time\n"), 0);
		*i += 2;
		skip_whitespaces(line, i);
		(*config)->we_tex = ft_strdup(&line[*i]);
		if (!(*config)->we_tex)
			return (0);
	}
	else
	{
		printf("Error : Wrong key find in file\n");
		return (0);
	}
	return (1);
}

int	fill_element_ter(char *line, t_configuration **config, int *i)
{
	if (ft_strncmp(&line[*i], "F ", 2) == 0)
	{
		if ((*config)->fl_color[0] != 0 || (*config)->fl_color[1] != 0
			|| (*config)->fl_color[2] != 0)
			return (ft_printf("F key find multiple time\n"), 0);
		*i += 1;
		skip_whitespaces(line, i);
		fill_floor_ceiling_color((*config)->fl_color, line, i);
	}
	else if (ft_strncmp(&line[*i], "C ", 2) == 0)
	{
		if ((*config)->c_color[0] != 0 || (*config)->c_color[1] != 0
			|| (*config)->c_color[2] != 0)
			return (ft_printf("C key find multiple time\n"), 0);
		*i += 1;
		skip_whitespaces(line, i);
		fill_floor_ceiling_color((*config)->c_color, line, i);
	}
	else
		return (fill_element_quater(line, config, i));
	return (1);
}

int	fill_element_bis(char *line, t_configuration **config, int *i)
{
	if (ft_strncmp(&line[*i], "EA ", 3) == 0)
	{
		if ((*config)->ea_tex)
			return (ft_printf("EA key find multiple time\n"), 0);
		*i += 2;
		skip_whitespaces(line, i);
		(*config)->ea_tex = ft_strdup(&line[*i]);
		if (!(*config)->ea_tex)
			return (0);
	}
	else if (ft_strncmp(&line[*i], "NO ", 3) == 0)
	{
		if ((*config)->no_tex)
			return (ft_printf("NO key find multiple time\n"), 0);
		*i += 2;
		skip_whitespaces(line, i);
		(*config)->no_tex = ft_strdup(&line[*i]);
		if (!(*config)->no_tex)
			return (0);
	}
	else
		return (fill_element_ter(line, config, i));
	return (1);
}

int	fill_element(char *line, t_configuration **config)
{
	int	i;

	i = 0;
	skip_whitespaces(line, &i);
	if (ft_strncmp(&line[i], "SO ", 3) == 0)
	{
		if ((*config)->so_tex)
			return (ft_printf("SO key find multiple time\n"), 0);
		i += 2;
		skip_whitespaces(line, &i);
		(*config)->so_tex = ft_strdup(&line[i]);
		if (!(*config)->so_tex)
			return (0);
	}
	else
		return (fill_element_bis(line, config, &i));
	return (1);
}

int	fill_map_line(char *line, t_configuration **config, int i, int j)
{
	while (line[i])
	{
		if (line[i] == '1' || line[i] == '0' || line[i] == 'N' || line[i] == 'S'
			|| line[i] == 'E' || line[i] == 'W')
		{
			if (line[i] == '1' || line[i] == '0')
				(*config)->map[(*config)->n_rows][j++] = line[i] - 48;
			else
			{
				(*config)->map[(*config)->n_rows][j++] = 3;
				(*config)->orientation = line[i];
			}
		}
		else if (ft_iswhitespace(line[i]))
			(*config)->map[(*config)->n_rows][j++] = 1;
		else
			return (ft_printf("Error : Wrong key find in map\n"), 0);
		i++;
	}
	if (j < (*config)->n_column)
	{
		while (j < (*config)->n_column)
			(*config)->map[(*config)->n_rows][j++] = 9;
	}
	return (1);
}

int	fill_map(char *line, t_configuration **config)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	if (!realloc_map(config))
		return (0);
	(*config)->map[(*config)->n_rows] = malloc(sizeof(int)
			* (*config)->n_column);
	if (!(*config)->map[(*config)->n_rows])
		return (0);
	while (ft_iswhitespace(line[i]))
	{
		(*config)->map[(*config)->n_rows][j++] = 1;
		i++;
	}
	if (!fill_map_line(line, config, i, j))
		return (0);
	(*config)->n_rows++;
	return (1);
}

/*int	fill_map(char *line, t_configuration **config)
{
	int	i;
	int	j;
	int	**map;
	
	i = 0;
	j = 0;
	//skip_whitespaces(line, &i);
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
		else if (ft_iswhitespace(line[i]))
			(*config)->map[(*config)->n_rows][j] = 0;
		else
		{
			printf("Error : Wrong key find in map\n");
			return (0);
		}
		i++;
	}
	if (j > (*config)->n_column)
		(*config)->n_column = j;
	(*config)->n_rows++;
	return (1);
}*/