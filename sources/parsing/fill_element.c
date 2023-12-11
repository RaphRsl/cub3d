/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_element.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toteixei <toteixei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 15:25:49 by toteixei          #+#    #+#             */
/*   Updated: 2023/12/11 09:38:05 by toteixei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int	fill_element_ter(char *line, t_configuration **config, int *i)
{
	if (ft_strncmp(&line[*i], "F ", 2) == 0)
	{
		if ((*config)->fl_color[0] != -1 || (*config)->fl_color[1] != -1
			|| (*config)->fl_color[2] != -1)
			return (ft_printf("Error\nF key find multiple time\n"), 0);
		*i += 1;
		skip_whitespaces(line, i);
		fill_floor_ceiling_color((*config)->fl_color, line, i);
	}
	else if (ft_strncmp(&line[*i], "C ", 2) == 0)
	{
		if ((*config)->c_color[0] != -1 || (*config)->c_color[1] != -1
			|| (*config)->c_color[2] != -1)
			return (ft_printf("Error\nC key find multiple time\n"), 0);
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
			return (ft_printf("Error\nEA key find multiple time\n"), 0);
		*i += 2;
		skip_whitespaces(line, i);
		(*config)->ea_tex = ft_strdup(&line[*i]);
		if (!(*config)->ea_tex)
			return (0);
	}
	else if (ft_strncmp(&line[*i], "NO ", 3) == 0)
	{
		if ((*config)->no_tex)
			return (ft_printf("Error\nNO key find multiple time\n"), 0);
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
	if ((*config)->map != NULL)
		return (ft_printf("Error\nMap not at the EOF.\n"), 0);
	skip_whitespaces(line, &i);
	if (ft_strncmp(&line[i], "SO ", 3) == 0)
	{
		if ((*config)->so_tex)
			return (ft_printf("Error\nSO key find multiple time\n"), 0);
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
	while (line[++i])
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
			return (free((*config)->map[(*config)->n_rows]),
				ft_printf("Error : Wrong key find in map\n"), 0);
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
	if (!fill_map_line(line, config, i - 1, j))
		return (0);
	(*config)->n_rows++;
	return (1);
}
