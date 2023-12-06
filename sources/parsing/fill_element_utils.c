/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_element_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toteixei <toteixei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 15:26:42 by toteixei          #+#    #+#             */
/*   Updated: 2023/12/06 16:17:08 by toteixei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int	is_map(char *line, t_configuration *config)
{
	int	i;

	i = 0;
	if (!config->ea_tex || !config->we_tex || !config->so_tex || !config->no_tex)
		return (0);
	skip_whitespaces(line, &i);
	if (line[i] == '1' || line[i] == '0' || line[i] == 'N' || line[i] == 'S' || line[i] == 'E' || line[i] == 'W')
		return (1);
	return (0);
}

int	is_key(char *line, int i)
{
	if (line[i] && line[i + 1] && (line[i] == 'F' || line[i] == 'C') && line[i + 1] == ' ')
		return (1);
	else if (line[i] && line[i + 1] && line[i + 2] && ft_isalpha(line[i]) && ft_isalpha(line[i + 1]) && line[i + 2] == ' ')
		return (1);
	return (0);
}

int	is_element(char *line)
{
	int	i;

	i = 0;
	skip_whitespaces(line, &i);
	if (line[i] && line[i + 1] && (line[i] == 'F' || line[i] == 'C') && line[i + 1] == ' ')
		return (1);
	else if (line[i] && line[i + 1] && line[i + 2] && ft_isalpha(line[i]) && ft_isalpha(line[i + 1]) && line[i + 2] == ' ')
		return (1);
	return (0);
	// if (ft_strncmp(&line[i], "SO ", 3) == 0)
	// 	return (1);
	// else if (ft_strncmp(&line[i], "WE ", 3) == 0)
	// 	return (1);
	// else if (ft_strncmp(&line[i], "NO ", 3) == 0)
	// 	return (1);
	// else if (ft_strncmp(&line[i], "EA ", 3) == 0)
	// 	return (1);
	// else if (ft_strncmp(&line[i], "F ", 2) == 0)
	// 	return (1);
	// else if (ft_strncmp(&line[i], "C ", 2) == 0)
	// 	return (1);
	// else
	// 	ft_printf("Error\nWrong element\n");
}

void	skip_whitespaces(char *line, int *i)
{
	while (ft_iswhitespace(line[*i]))
		(*i)++;
}