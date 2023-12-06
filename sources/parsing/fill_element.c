/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_element.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toteixei <toteixei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 15:25:49 by toteixei          #+#    #+#             */
/*   Updated: 2023/12/06 16:14:56 by toteixei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

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
		if ((*config)->ea_tex)
			return (ft_printf("EA key find multiple time\n"), 0);
		*i += 2;
		skip_whitespaces(line, i);
		(*config)->ea_tex = ft_strdup(&line[*i]);
		if (!(*config)->ea_tex)
			return (0);
    }
    else if (ft_strncmp(line, "F ", 2) == 0)
    {
        if ((*config)->fl_color[0] != 0 || (*config)->fl_color[1] != 0 || (*config)->fl_color[2] != 0)
			return (ft_printf("F key find multiple time\n"), 0);
		*i += 1;
		skip_whitespaces(line, i);
		fill_floor_ceiling_color((*config)->fl_color, line, i);
		
    }
    else if (ft_strncmp(line, "C ", 2) == 0)
    {
		if ((*config)->c_color[0] != 0 || (*config)->c_color[1] != 0 || (*config)->c_color[2] != 0)
			return (ft_printf("C key find multiple time\n"), 0);
        *i += 1;
		skip_whitespaces(line, i);
		fill_floor_ceiling_color((*config)->c_color, line, i);
    }
	else
	{
		printf("Error : Wrong key find in file\n");
		return (0);
	}
	return (1);
}

int fill_element(char *line, t_configuration **config, int *i)
{
    if (ft_strncmp(line, "SO ", 3) == 0)
    {
		if ((*config)->so_tex)
			return (ft_printf("SO key find multiple time\n"), 0);
		*i += 2;
		skip_whitespaces(line, i);
		(*config)->so_tex = ft_strdup(&line[*i]);
		if (!(*config)->so_tex)
			return (0);
    }
    else if (ft_strncmp(line, "WE ", 3) == 0)
    {
		if ((*config)->we_tex)
			return (ft_printf("WE key find multiple time\n"), 0);
		*i += 2;
		skip_whitespaces(line, i);
		(*config)->we_tex = ft_strdup(&line[*i]);
		if (!(*config)->we_tex)
			return (0);
    }
    else if (ft_strncmp(line, "NO ", 3) == 0)
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
		return (fill_element_bis(line, config, i));
    return (1);
}

int	fill_map(char *line, t_configuration **config)
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
	(*config)->map[(*config)->n_rows] = malloc(sizeof(int) * (*config)->n_column);
	if (!(*config)->map[(*config)->n_rows])
		return (0);
	j = 0;
	while(ft_iswhitespace(line[i]))
	{
		(*config)->map[(*config)->n_rows][j++] = 1;
		i++;
	}
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
		{
			(*config)->map[(*config)->n_rows][j] = 1;
			j++;
		}
		else
		{
			ft_printf("Error : Wrong key find in map\n");
			printf("'%d' in line %d in column %d\n", line[i], (*config)->n_rows, j);
			return (0);
		}
		i++;
	}
	if (j < (*config)->n_column)
	{
		while (j < (*config)->n_column)
		{
			(*config)->map[(*config)->n_rows][j] = 9;
			j++;
		}
	}
	//if (j > (*config)->n_column)
	//	(*config)->n_column = j;
	(*config)->n_rows++;
	return (1);
}


// int	fill_map(char *line, t_configuration **config)
// {
// 	int	i;
// 	int	j;
// 	int	**map;
	
// 	i = 0;
// 	j = 0;
// 	//skip_whitespaces(line, &i);
// 	if (!(*config)->map)
// 	{
// 		(*config)->map = malloc(sizeof(int *) * 1);
// 		if (!(*config)->map)
// 			return (0);
// 	}
// 	else
// 	{
// 		map = malloc(sizeof(int *) * ((*config)->n_rows + 1));
// 		if (!map)
// 			return (0);
// 		while (j < (*config)->n_rows)
// 		{
// 			map[j] = (*config)->map[j];
// 			j++;
// 		}
// 		free((*config)->map);
// 		(*config)->map = map;
// 	}
// 	(*config)->map[(*config)->n_rows] = malloc(sizeof(int) * ft_strlen(&line[i]));
// 	if (!(*config)->map[(*config)->n_rows])
// 		return (0);
// 	j = 0;
// 	while (line[i])
// 	{
// 		if (line[i] == '1' || line[i] == '0' || line[i] == 'N' || line[i] == 'S' || line[i] == 'E' || line[i] == 'W')
// 		{
// 			if (line[i] == '1' || line[i] == '0')
// 				(*config)->map[(*config)->n_rows][j] = line[i] - 48;
// 			else
// 			{
// 				(*config)->map[(*config)->n_rows][j] = 3;
// 				(*config)->orientation = line[i];
// 			}
// 			j++;
// 		}
// 		else if (ft_iswhitespace(line[i]))
// 			(*config)->map[(*config)->n_rows][j] = 0;
// 		else
// 		{
// 			printf("Error : Wrong key find in map\n");
// 			return (0);
// 		}
// 		i++;
// 	}
// 	if (j > (*config)->n_column)
// 		(*config)->n_column = j;
// 	(*config)->n_rows++;
// 	return (1);
// }