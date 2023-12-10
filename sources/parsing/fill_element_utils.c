/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_element_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tomteixeira <tomteixeira@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 15:26:42 by toteixei          #+#    #+#             */
/*   Updated: 2023/12/10 17:39:44 by tomteixeira      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int	is_map(char *line, t_configuration *config)
{
	int	i;

	i = 0;
	(void)config;
	//if (!config->ea_tex || !config->we_tex
	//	|| !config->so_tex || !config->no_tex)
	//	return (0);
	skip_whitespaces(line, &i);
	if (line[i] == '1' || line[i] == '0'
		|| line[i] == 'N' || line[i] == 'S' || line[i] == 'E' || line[i] == 'W')
		return (1);
	return (0);
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

int	realloc_map(t_configuration **config)
{
	int	j;
	int	**map;

	j = 0;
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
	return (1);
}

int	is_element(char *line)
{
	int	i;

	i = 0;
	skip_whitespaces(line, &i);
	if (ft_isprint(line[i]) && !ft_isdigit(line[i]))
	{
		return (1);
	}
	// if (line[i] && line[i + 1]
	// 	&& (line[i] == 'F' || line[i] == 'C') && line[i + 1] == ' ')
	// 	return (1);
	// else if (line[i] && line[i + 1] && line[i + 2]
	// 	&& ft_isalpha(line[i]) && ft_isalpha(line[i + 1]) && line[i + 2] == ' ')
	// 	return (1);
	return (0);
}

void	skip_whitespaces(char *line, int *i)
{
	while (ft_iswhitespace(line[*i]))
		(*i)++;
}
